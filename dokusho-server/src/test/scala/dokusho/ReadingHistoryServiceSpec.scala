package dokusho

import cats.effect.IO
import org.scalatest.FreeSpec

class ReadingHistoryServiceSpec extends FreeSpec {

  val readingHistoryService = new ReadingHistoryService(mockRepository("userId"))

  "ReadingHistoryService" - {

    "getReadingHistory" - {

      "when the user exists" - {
        "should return the user" in {
          val result = readingHistoryService.getReadingHistory("userId").unsafeRunSync()
          assert(result.nonEmpty)
          assert(result.get.userId == "userId")
        }
      }
      "when the user does not exist" - {
        "should return an empty option" in {
          assert(readingHistoryService.getReadingHistory("i don't exist").unsafeRunSync().isEmpty)
        }
      }

    }
  }

  private def mockRepository(validUser: String) = new HistoryRepository {
    val history = UserReadingHistory(validUser, ReadingHistory(Seq(Day("Today", Seq.empty))))
    override def get(userId: String): IO[Option[UserReadingHistory]] =
      if (userId == validUser) IO.pure(Some(history))
      else IO.pure(None)

    override def put(g: UserReadingHistory): IO[UserReadingHistory] = IO.pure(g)
  }
}
