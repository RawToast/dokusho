package dokusho

import java.time.LocalDate

import cats.data.OptionT
import cats.effect.IO
import monocle.macros.GenLens

class ReadingHistoryService(mongoRepository: MongoRepository) {

  def getReadingHistory(userId: String): IO[Option[UserReadingHistory]] =
    mongoRepository.get(userId)

  def addNewEntry(userId: String, entry: Entry): IO[Option[UserReadingHistory]] = {
    lazy val update = daysLens.modify(updateDay(entry))
    OptionT(getReadingHistory(userId))
      .map(update)
      .semiflatMap(upsert)
      .value
  }

  def upsert(userReadingHistory: UserReadingHistory): IO[UserReadingHistory] =
    mongoRepository.put(userReadingHistory)

  private lazy val daysLens = GenLens[UserReadingHistory](_.readingHistory.days)

  private def updateDay(entry: Entry)(days: Seq[Day]) = {
    val newDay = Day(LocalDate.now().atStartOfDay().toString, Seq.empty)
    val ndays = if (days.exists(_.date == newDay.date)) days else newDay +: days

    ndays.withFilter(_.date == newDay.date)
      .map(d => d.copy(entries = entry +: d.entries))
  }
}