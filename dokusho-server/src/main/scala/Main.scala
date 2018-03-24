import cats.effect._
import dokusho.{MongoRepository, ReadingHistoryEndpoint, ReadingHistoryService}
import fs2.StreamApp.ExitCode
import fs2.{Stream, StreamApp}
import org.http4s.server.ServerBuilder
import org.http4s.server.blaze.BlazeBuilder

import scala.concurrent.ExecutionContext.Implicits.global

object Main extends StreamApp[IO]  {

  //TODO move to .env
  lazy val mongo = new MongoRepository(
    "mongodb://mongo:27017",
    "test",
    "dokusho")

  val readingHistoryService = new ReadingHistoryService(mongo)
  val historyService = new ReadingHistoryEndpoint(readingHistoryService)


  override def stream(args: List[String], requestShutdown: IO[Unit]): Stream[IO, ExitCode] =
    BlazeBuilder[IO]
      .bindHttp(8080, "0.0.0.0")
      .mountService(historyService.routes, "/")
      .withBanner(ServerBuilder.DefaultBanner)
      .serve
}