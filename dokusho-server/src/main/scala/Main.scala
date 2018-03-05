import cats.effect._
import dokusho.{MongoRepository, MongoService}
import org.http4s.dsl.io._
import org.http4s.server.blaze.BlazeBuilder
import fs2.{Stream, StreamApp}
import fs2.StreamApp.ExitCode
import org.http4s.server.ServerBuilder

import scala.concurrent.ExecutionContext.Implicits.global

object Main extends StreamApp[IO]  {

  //TODO move to .env
  lazy val mongo = new MongoRepository(
    "mongodb://mongo:27017",
    "test",
    "dokusho")

  val mongoService = new MongoService(mongo)


  override def stream(args: List[String], requestShutdown: IO[Unit]): Stream[IO, ExitCode] =
    BlazeBuilder[IO]
      .bindHttp(8080, "localhost")
      .mountService(mongoService.routes, "/")
      .withBanner(ServerBuilder.DefaultBanner)
      .serve
}