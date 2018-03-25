package dokusho

import cats.effect.IO
import io.circe.Json
import io.circe.generic.auto._
import io.circe.syntax._
import org.http4s._
import org.http4s.circe._
import org.http4s.dsl.io.{->, /, GET, Ok, Root, _}

class ReadingHistoryRouter(readingHistoryService: ReadingHistoryService) {

  case class SuccessfulPut(userId: String)

  val routes: HttpService[IO] = HttpService[IO] {
    case GET -> Root / "history" / userId =>
        for {
          userReadingHistory <- readingHistoryService.getReadingHistory(userId)
          json: Option[Json] = userReadingHistory.map(_.asJson)
          resp <- json.fold(NotFound())(j => Ok(j))
        } yield resp
    case req@PUT -> Root / "history" / userId =>
      implicit val userDecoder: EntityDecoder[IO, ReadingHistory] = jsonOf[IO, ReadingHistory]
      for {
        readingHistory <- req.as[ReadingHistory]
        storedHistory <- readingHistoryService.upsert(UserReadingHistory(userId, readingHistory))
        json: Json = SuccessfulPut(storedHistory.userId).asJson
        response <- Ok(json)
      } yield response
    case req@POST -> Root / "history" / userId / "add" =>
      implicit val entryDecoder: EntityDecoder[IO, NewEntry] = jsonOf[IO, NewEntry]
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