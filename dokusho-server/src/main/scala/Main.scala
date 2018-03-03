import com.twitter.finagle.Http
import com.twitter.util.Await

import io.finch._
import io.finch.circe._
import io.finch.syntax._
import io.circe.generic.auto._

object Main extends App {

  case class Locale(language: String, country: String)
  case class Time(locale: Locale, time: String)

  def currentTime(l: java.util.Locale): String =
    java.util.Calendar.getInstance(l).getTime.toString

  val time: Endpoint[Time] =
    post("time" :: jsonBody[Locale]) { l: Locale =>
      Ok(Time(l, currentTime(new java.util.Locale(l.language, l.country))))
    }

  Await.ready(Http.server.serve(":8081", time.toService))
}