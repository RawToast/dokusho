package dokusho

import cats.effect.IO
import io.circe.Json
import io.circe.generic.auto._
import io.circe.syntax._
import org.http4s._
import org.http4s.circe._
import org.http4s.dsl.io.{->, /, GET, Ok, Root, _}

class MongoService(mongoRepository: MongoRepository) {

  case class SuccessfulPut(userId: String)

  val routes: HttpService[IO] = HttpService[IO] {
    case GET -> Root / "history" / userId =>
      for {
        userReadingHistory <- mongoRepository.getUnsafe(userId)
        json = userReadingHistory.asJson
        response <- Ok(json)
      } yield response
    case req@PUT -> Root / "history" / userId =>
      implicit val userDecoder: EntityDecoder[IO, ReadingHistory] = jsonOf[IO, ReadingHistory]
      for {
        userReadingHistory <- req.as[ReadingHistory]
        storedHistory <- mongoRepository.put(UserReadingHistory(userId, userReadingHistory))
        json: Json = SuccessfulPut(storedHistory.userId).asJson
        response <- Ok(json)
      } yield response
  }
}