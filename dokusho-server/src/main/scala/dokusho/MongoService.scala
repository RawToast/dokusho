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
    case GET -> Root / "mongo" / name =>
      for {
        userReadingHistory <- mongoRepository.get(name)
        json: Json = userReadingHistory.asJson
        response <- Ok(json)
      } yield response
    case req@PUT -> Root / "mongo" =>
      implicit val userDecoder: EntityDecoder[IO, UserReadingHistory] = jsonOf[IO, UserReadingHistory]
      for {
        userReadingHistory <- req.as[UserReadingHistory]
        storedHistory <- mongoRepository.put(userReadingHistory)
        json: Json = SuccessfulPut(storedHistory.userId).asJson
        response <- Ok(json)
      } yield response
  }
}