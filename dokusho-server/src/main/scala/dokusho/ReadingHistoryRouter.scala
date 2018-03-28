package dokusho

import cats.effect.IO
import io.circe.Json
import org.http4s.HttpService

class ReadingHistoryRouter(readingHistoryService: ReadingHistoryService) extends Http4sRouter {

  case class SuccessfulPut(userId: String)

  val routes: HttpService[IO] = HttpService[IO] {
    case GET -> Root / "history" / userId =>
      for {
        userReadingHistory <- readingHistoryService.getReadingHistory(userId)
        json: Option[Json] = userReadingHistory.map(_.asJson)
        resp <- json.fold(NotFound())(j => Ok(j))
      } yield resp
    case req@PUT -> Root / "history" / userId =>
      for {
        readingHistory <- req.as[ReadingHistory]
        storedHistory <- readingHistoryService.upsert(UserReadingHistory(userId, readingHistory))
        json: Json = SuccessfulPut(storedHistory.userId).asJson
        response <- Ok(json)
      } yield response
    case req@POST -> Root / "history" / userId / "add" =>
      for {
        entry <- req.as[NewEntry]
        storedHistory <- readingHistoryService.addNewEntry(userId, entry)
        json = storedHistory.map(_.asJson)
        result <- json.fold(NotFound())(j => Ok(j))
      } yield result
    case PUT -> Root / "history" / userId / "reset" =>
      readingHistoryService.reset(userId)
        .map(_.asJson)
        .flatMap(j => Ok(j))
  }
}
