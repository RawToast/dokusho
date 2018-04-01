package dokusho

import cats.data.OptionT
import cats.effect.IO
import io.circe.Json
import org.http4s.util.CaseInsensitiveString
import org.http4s.{Header, HttpService, Request, Response}

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

class AltReadingHistoryRouter(readingHistoryService: ReadingHistoryService) extends Http4sRouter {

  case class SuccessfulPut(userId: String)

  def getUserId(req: Request[IO]): IO[Option[String]] =
    IO(req.headers.find(_.name == CaseInsensitiveString("User")).map(_.value))

  implicit private def routeWithErrorHandling(io: OptionT[IO, IO[Response[IO]]]): IO[Response[IO]] =
    io.value.flatMap(_.getOrElse(NotFound()))

  val routes: HttpService[IO] = HttpService[IO] {
    case req@GET -> Root / "history" =>
      for {
        userId <- OptionT(getUserId(req))
        userReadingHistory <- OptionT(readingHistoryService.getReadingHistory(userId))
        json: Json = userReadingHistory.asJson
        resp = Ok(json)
      } yield resp
    case req@PUT -> Root / "history" =>
      for {
        userId <- OptionT(getUserId(req))
        readingHistory <- OptionT.liftF(req.as[ReadingHistory])
        storedHistory <- OptionT.liftF(readingHistoryService.upsert(UserReadingHistory(userId, readingHistory)))
        json: Json = SuccessfulPut(storedHistory.userId).asJson
        response = Ok(json)
      } yield response
    case req@POST -> Root / "history" / "add" =>
      for {
        userId <- OptionT(getUserId(req))
        entry <- OptionT.liftF(req.as[NewEntry])
        storedHistory <- OptionT(readingHistoryService.addNewEntry(userId, entry))
        json = storedHistory.asJson
        response = Ok(json)
      } yield response
    case req@PUT -> Root / "history" / "reset" =>
      OptionT(getUserId(req))
      .semiflatMap(userId => readingHistoryService.reset(userId))
      .map(_.asJson)
      .map(j => Ok(j))
    case req@GET -> Root / "auth" => {
      // This endpoint should be removed, but right now it's handy for development
      val headerOpt: Header = req.headers
                              .find(_.name == CaseInsensitiveString("User"))
                              .getOrElse(Header("User", "None"))

      Ok("Hello: " + headerOpt.value)
    }
  }
}
