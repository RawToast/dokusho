import cats.effect._
import org.http4s._
import org.http4s.dsl.io._
import org.http4s.server.blaze.BlazeBuilder
import fs2.{Stream, StreamApp}
import fs2.StreamApp.ExitCode
import org.http4s.server.ServerBuilder

import scala.concurrent.ExecutionContext.Implicits.global

object Main extends StreamApp[IO] {

  val helloWorldService = HttpService[IO] {
    case GET -> Root / "hello" / name =>
      Ok(s"Hello, $name.")
  }


  val builder = BlazeBuilder[IO].bindHttp(8080, "localhost")
    .mountService(helloWorldService, "/")
    .start


  override def stream(args: List[String], requestShutdown: IO[Unit]): Stream[IO, ExitCode] =
    BlazeBuilder[IO]
      .bindHttp(8080, "localhost")
      .mountService(helloWorldService, "/")
      .withBanner(ServerBuilder.DefaultBanner)
      .serve
}