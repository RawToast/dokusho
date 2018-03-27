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

  def addNewEntry(userId: String, newEntry: NewEntry): IO[Option[UserReadingHistory]] = {
    lazy val update = daysLens.modify(updateDay(newEntry))
    OptionT(getReadingHistory(userId))
      .map(update)
      .semiflatMap(upsert)
      .value
  }

  def upsert(userReadingHistory: UserReadingHistory): IO[UserReadingHistory] =
    mongoRepository.put(userReadingHistory)

  def reset(userId: String): IO[UserReadingHistory] = {
    val emptyHistory = UserReadingHistory(userId, ReadingHistory(Seq.empty))
    upsert(emptyHistory)
  }

  private def updateDay(entry: NewEntry)(days: Seq[Day]) = {
    val currentDay = Day(LocalDate.now().atStartOfDay().toString, Seq.empty)

    val updateDayWithEntry = addEntry(entry)
    val daysWithUpdatedDay =
      if (days.exists(_.date == currentDay.date)) days
      else currentDay +: days

    daysWithUpdatedDay
      .map(d => if (d.date == currentDay.date) updateDayWithEntry(d) else d)
  }

  private def addEntry(entry: NewEntry) = entriesLens
    .modify { es => Entry(getNextId(es), entry.kind, entry.value) +: es}

  private def getNextId(entries: Seq[Entry]) = 1l +
    entries.foldLeft(-1l)((currMax, entry) => Math.max(currMax, entry.id))
}
