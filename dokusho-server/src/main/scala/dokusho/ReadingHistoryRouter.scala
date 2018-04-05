package dokusho

import cats.data.OptionT
import cats.effect.IO
import org.http4s.util.CaseInsensitiveString
import org.http4s.{HttpService, Request, Response}

class ReadingHistoryRouter(readingHistoryService: ReadingHistoryService) extends Http4sRouter {
  private val service = readingHistoryService

  case class SuccessfulPut(userId: String)

  def getUserId(req: Request[IO]): IO[Option[String]] =
    IO(req.headers.find(_.name == CaseInsensitiveString("User")).map(_.value))

  implicit class ReqHelper(req: Request[IO]) {
    def withReadingHistory(f: ReadingHistory => IO[UserReadingHistory]): IO[UserReadingHistory] =
      req.as[ReadingHistory].flatMap(f(_))

    def withEntry(f: NewEntry => IO[UserReadingHistory]): IO[UserReadingHistory] =
      req.as[NewEntry].flatMap(f(_))
  }

  implicit private def routeWithErrorHandling(io: OptionT[IO, IO[Response[IO]]]): IO[Response[IO]] =
    io.value.flatMap(_.getOrElse(NotFound()))

  val orNotFound = (io: OptionT[IO, IO[Response[IO]]]) =>
    io.value.flatMap(_.getOrElse(NotFound()))

  val routes: HttpService[IO] = HttpService[IO] {
    case req@GET -> Root / "history" =>
      OptionT(getUserId(req))
      .flatMapF(userId => service.getReadingHistorySummary(userId))
      .map(_.asJson)
      .map(json => Ok(json))
      .value.flatMap(_.getOrElse(NotFound()))
    case req@PUT -> Root / "history" =>
      OptionT(getUserId(req))
      .semiflatMap(userId => req.withReadingHistory(rh => service.upsert(UserReadingHistory(userId, rh))))
      .map(storedHistory => SuccessfulPut(storedHistory.userId))
      .map(sp => Ok(sp.asJson))
      .value.flatMap(_.getOrElse(NotFound()))
    case req@POST -> Root / "history" / "add" =>
      OptionT(getUserId(req))
      .semiflatMap(userId => req.withEntry(e => service.upsertNewEntry(userId, e)))
      .map(storedHistory => storedHistory.asJson)
      .map(json => Ok(json))
      .value.flatMap(_.getOrElse(BadRequest()))
    case req@PUT -> Root / "history" / "reset" =>
      OptionT(getUserId(req))
      .semiflatMap(userId => service.reset(userId))
      .map(_.asJson)
      .map(j => Ok(j))
      .value.flatMap(_.getOrElse(BadRequest()))
  }
}
