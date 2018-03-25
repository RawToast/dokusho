package dokusho

import java.time.LocalDate

import cats.data.OptionT
import cats.effect.IO
import monocle.macros.GenLens

class ReadingHistoryService(mongoRepository: MongoRepository) {

  private lazy val daysLens = GenLens[UserReadingHistory](_.readingHistory.days)
  private lazy val entriesLens = GenLens[Day](_.entries)

  def getReadingHistory(userId: String): IO[Option[UserReadingHistory]] =
    mongoRepository.get(userId)

  def addNewEntry(userId: String, entry: NewEntry): IO[Option[UserReadingHistory]] = {
    lazy val update = daysLens.modify(updateDay(entry))
    OptionT(getReadingHistory(userId))
      .map(update)
      .semiflatMap(upsert)
      .value
  }

  def upsert(userReadingHistory: UserReadingHistory): IO[UserReadingHistory] =
    mongoRepository.put(userReadingHistory)

  private def updateDay(entry: NewEntry)(days: Seq[Day]) = {
    val currentDay = Day(LocalDate.now().atStartOfDay().toString, Seq.empty)

    val daysWithUpdatedDay =
      if (days.exists(_.date == currentDay.date)) days
      else currentDay +: days

    daysWithUpdatedDay.withFilter(_.date == currentDay.date)
        .map(addEntry(entry))
  }

  private def addEntry(entry: NewEntry) = entriesLens
    .modify { es => Entry(getNextId(es), entry.kind, entry.value) +: es}

  private def getNextId(entries: Seq[Entry]) =
    entries.foldLeft(0l)((currMax, entry) => Math.max(currMax, entry.id))
}
