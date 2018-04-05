package dokusho

import cats.effect.IO
import org.scalatest.FreeSpec

class ReadingHistoryServiceSpec extends FreeSpec {

  val readingHistoryService = new ReadingHistoryService(stubRepository("userId"))

  "ReadingHistoryService" - {

    "getReadingHistory" - {

      "when the user exists" - {
        "should return the user" in {
          val result = readingHistoryService.getReadingHistory("userId").unsafeRunSync()
          assert(result.nonEmpty)
          assert(result.map(_.userId).contains("userId"))
        }
      }
      "when the user does not exist" - {
        "should return an empty option" in {
          assert(readingHistoryService.getReadingHistory("i don't exist").unsafeRunSync().isEmpty)
        }
      }
    }

    "addNewEntry" - {
      "when the user exists" - {
        "and no entries exist for the date" - {

          lazy val newEntry = NewEntry(Book, 1)
          lazy val result = new ReadingHistoryService(stubRepository("userId"))
            .addNewEntry("userId", newEntry).unsafeRunSync()

          "should return the users updated history" in {
            assert(result.nonEmpty)
            assert(result.map(_.userId).contains("userId"))
          }

          "should insert a new day" in {
            val days = result.map(_.readingHistory.days).getOrElse(Seq.empty)
            assert(days.size == 1)
          }
        }

        "and entries exist for the date" - {
          lazy val previousEntry1 = NewEntry(Book, 1)
          lazy val previousEntry2 = NewEntry(Manga, 1)
          lazy val newEntry = NewEntry(Book, 1)

          lazy val result = {
            val rhs = new ReadingHistoryService(stubRepository("userId"))
            rhs.addNewEntry("userId", previousEntry1).unsafeRunSync()
            rhs.addNewEntry("userId", previousEntry2).unsafeRunSync()
            rhs.addNewEntry("userId", newEntry).unsafeRunSync()
          }

          "should return the users updated history" in {
            assert(result.nonEmpty)
            assert(result.map(_.userId).contains("userId"))
          }

          "should not insert a second day" in {
            val days = result.map(_.readingHistory.days).getOrElse(Seq.empty)
            assert(days.size == 1)
          }

          "should include both entries" in {
            val days = result
                       .flatMap(_.readingHistory.days.headOption)
                       .getOrElse(Day("No", Seq()))
            assert(days.date != "No")
            assert(days.entries.size == 2)
            assert(days.entries.exists(e => (e.kind == previousEntry2.kind) && e.value == previousEntry2.value))
            assert(days.entries.exists(e => e.kind == newEntry.kind))
          }

          "should combine with any existing entries for the same page type" in {
            val days = result
                       .flatMap(_.readingHistory.days.headOption)
                       .getOrElse(Day("No", Seq()))
            assert(days.date != "No")
            assert(days.entries.exists(e => (e.kind == newEntry.kind) && e.value == previousEntry1.value + newEntry.value))
          }
        }
      }
    }
  }

  private def stubRepository(validUser: String) = new HistoryRepository {
    val testReadingHistory = ReadingHistory(Seq())
    private var history = UserReadingHistory(validUser, testReadingHistory)

    override def get(userId: String): IO[Option[UserReadingHistory]] =
      if (userId == validUser) IO.pure(Some(history))
      else IO.pure(None)

    override def put(g: UserReadingHistory): IO[UserReadingHistory] = {
      history = g
      IO.pure(g)
    }
  }
}
