package dokusho

// import java.time.LocalDate

// import cats.data.OptionT
// import cats.effect.IO
// import monocle.macros.GenLens

trait ReadingHistoryService[F[_]]:
  def getReadingHistory(userId: String): F[Option[UserReadingHistory]]
  def getReadingHistorySummary(userId: String): F[Option[UserReadingHistory]]
  def upsert(readingHistory: UserReadingHistory): F[UserReadingHistory]
  def upsertNewEntry(userId: String, newEntry: NewEntry): F[UserReadingHistory]
  def reset(userId: String): F[UserReadingHistory]


// class ReadingHistoryService(mongoRepository: HistoryRepository) {

//   private lazy val daysLens = GenLens[UserReadingHistory](_.readingHistory.days)
//   private lazy val entriesLens = GenLens[Day](_.entries)

//   def getReadingHistory(userId: String): IO[Option[UserReadingHistory]] =
//     mongoRepository.get(userId)

//   def getReadingHistorySummary(userId: String): IO[Option[UserReadingHistory]] =
//     OptionT(mongoRepository.get(userId))
//     .map(daysLens.modify(_.map(summarise))).value

//   private def summarise(day: Day): Day = {
//     import cats.implicits._

//     def getId(f: PageType): Long = f match {
//       case Book => 0
//       case Lyric => 1
//       case Manga => 2
//       case Net => 3
//       case News => 4
//     }

//     val summedEntries = day
//                         .entries
//                         .foldLeft(Map.empty[PageType, Int])((m, e) => m |+| Map(e.kind -> e.value))
//                         .toSeq
//                         .map { case (p: PageType, v: Int) => Entry(getId(p), p, v) }


//     day.copy(entries = summedEntries)
//   }


//   def getOrMakeReadingHistory(userId: String): IO[UserReadingHistory] =
//     OptionT(mongoRepository.get(userId))
//     .getOrElseF(reset(userId))

//   def addNewEntry(userId: String, newEntry: NewEntry): IO[Option[UserReadingHistory]] = {
//     lazy val update = daysLens.modify(updateDay(newEntry))
//     OptionT(getReadingHistory(userId))
//     .map(update)
//     .semiflatMap(upsert)
//     .map(daysLens.modify(_.map(summarise)))
//     .value
//   }

//   def upsertNewEntry(userId: String, newEntry: NewEntry): IO[UserReadingHistory] = {
//     lazy val update = daysLens.modify(updateDay(newEntry))
//     OptionT(getReadingHistory(userId))
//     .getOrElseF(reset(userId))
//     .map(update)
//     .flatMap(upsert)
//     .map(daysLens.modify(_.map(summarise)))
//   }

//   def upsert(userReadingHistory: UserReadingHistory): IO[UserReadingHistory] =
//     mongoRepository.put(userReadingHistory)

//   def reset(userId: String): IO[UserReadingHistory] = {
//     val emptyHistory = UserReadingHistory(userId, ReadingHistory(Seq.empty))
//     upsert(emptyHistory)
//   }

//   private def updateDay(entry: NewEntry)(days: Seq[Day]) = {
//     val currentDay = Day(LocalDate.now().atStartOfDay().toString, Seq.empty)

//     val updateDayWithEntry = addEntry(entry)
//     val daysWithUpdatedDay =
//       if (days.exists(_.date == currentDay.date)) days
//       else currentDay +: days

//     daysWithUpdatedDay
//     .map(d => if (d.date == currentDay.date)
//       updateDayWithEntry(d) else d)
//   }

//   private def addEntry(entry: NewEntry) = entriesLens
//                                           .modify { es => Entry(getNextId(es), entry.kind, entry.value) +: es }

//   private def getNextId(entries: Seq[Entry]) = 1l +
//     entries.foldLeft(-1l)((currMax, entry) => Math.max(currMax, entry.id))
// }
