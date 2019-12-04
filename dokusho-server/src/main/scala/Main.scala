import cats.effect._
import cats.implicits._
import dokusho.middleware.Auth0Middleware
import dokusho.{MongoRepository, ReadingHistoryRouter, ReadingHistoryService}
import org.http4s.dsl.io._
import org.http4s.implicits._
import org.http4s.client.Client
import org.http4s.client.blaze.Poo
import org.http4s.server.ServerBuilder
import org.http4s.server.blaze.BlazeServerBuilder

import scala.concurrent.ExecutionContext.Implicits.global

object Main extends IOApp  {

  //TODO move to .env
  lazy val mongo = new MongoRepository(
    "mongodb://mongo:27017",
    "test",
    "dokusho")

  lazy val pclient: Client[IO] = PooledHttp1Client[IO]()

  val authMiddleware: Auth0Middleware = new Auth0Middleware(pclient)
  val readingHistoryService = new ReadingHistoryService(mongo)
  val historyService = new ReadingHistoryRouter(readingHistoryService)

  val authHistory = authMiddleware.authenticationMiddleware(historyService.routes)


  def run(args: List[String]): IO[ExitCode] =
    BlazeServerBuilder[IO]
      .bindHttp(8080, "0.0.0.0")
      .mountService(historyService.routes, "/noauth")
      .mountService(authHistory, "/")
      .withBanner(ServerBuilder.DefaultBanner)
      .serve
      .compile
      .drain
      .as(ExitCode.Success)
}