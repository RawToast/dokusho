package dokusho.middleware

import cats.data.OptionT
import cats.effect.IO
import dokusho.Http4sRouter
import org.http4s._
import org.http4s.client.Client
import org.http4s.util.CaseInsensitiveString

sealed trait Auth0Response

case class AuthSuccessResponse(sub: String) extends Auth0Response

case class FailureResponse(reason: String) extends Auth0Response

class Auth0Middleware(client: Client[IO]) extends Http4sRouter {

  def authenticationMiddleware(service: HttpService[IO]): HttpService[IO] = cats.data.Kleisli { req: Request[IO] =>

    val authToken: Option[Header] =
      req.headers
      .find(_.name == CaseInsensitiveString("accessToken"))
      .map(header => Header.apply("Authorization", "Bearer " + header.value))

    authToken match {
      case Some(headers) =>
        OptionT(
          callService(client, headers)
          .map(userInfo => req.putHeaders(Header.apply("User", userInfo)))
          .flatMap(req => service.apply(req.putHeaders(headers)).value))
      case None =>
        val response: Response[IO] = Response.apply[IO](status = Unauthorized)
        OptionT(IO.pure(Option(response)))
    }
  }

  private def callService(c: Client[IO], authToken: Header): IO[String] = {
    println("Header: " + authToken.name + " " + authToken.value)

    c.fetch(Request.apply[IO](
      method = GET,
      uri = Uri.unsafeFromString("https://dokusho.eu.auth0.com/userinfo"),
      headers = Headers(authToken)
    )) { r =>
      r.status.responseClass match {
        case Status.Successful => r.as[AuthSuccessResponse]
        case _ => IO.apply(FailureResponse("unauthorised"))
      }
    }.map {
      case AuthSuccessResponse(sub: String) => println(s"Got sub: $sub"); sub.dropWhile(_ != '|').tail
      case FailureResponse(r: String) => r
    }
  }
}