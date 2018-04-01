import cats.effect.IO
import dokusho.middleware.Auth0Middleware
import dokusho.{MongoRepository, ReadingHistoryRouter, ReadingHistoryService}
import fs2.StreamApp.ExitCode
import fs2.{Stream, StreamApp}
import org.http4s.client.Client
import org.http4s.client.blaze.PooledHttp1Client
import org.http4s.server.ServerBuilder
import org.http4s.server.blaze.BlazeBuilder

import scala.concurrent.ExecutionContext.Implicits.global

object Main extends StreamApp[IO]  {

  //TODO move to .env
  lazy val mongo = new MongoRepository(
    "mongodb://mongo:27017",
    "test",
    "dokusho")

  lazy val pclient: Client[IO] = PooledHttp1Client[IO]()

  val authMiddleware: Auth0Middleware = new Auth0Middleware(pclient)

  val readingHistoryService = new ReadingHistoryService(mongo)
  val historyService: ReadingHistoryRouter = new ReadingHistoryRouter(readingHistoryService)
  val altHistoryService: ReadingHistoryRouter = new AltReadingHistoryRouter(readingHistoryService)

  val authHistory = authMiddleware.authenticationMiddleware(historyService.routes)


  override def stream(args: List[String], requestShutdown: IO[Unit]): Stream[IO, ExitCode] =
    BlazeBuilder[IO]
      .bindHttp(8080, "0.0.0.0")
      .mountService(historyService.routes, "/")
      .mountService(authHistory, "/authed")
      .withBanner(ServerBuilder.DefaultBanner)
      .serve
}