package dokusho

import cats.effect.{IO, Sync}
import io.circe.generic.AutoDerivation
import io.circe._
import org.http4s.EntityDecoder
import org.http4s.circe.CirceInstances
import org.http4s.dsl.Http4sDsl

/**
  * Utility trait with common implicits
  */
trait Http4sRouter extends AutoDerivation with CirceInstances with Http4sDsl[IO] {

  override val defaultPrinter: Printer =
    Printer.noSpaces

  override def jsonDecoder[F[_] : Sync]: EntityDecoder[F, Json] =
    CirceInstances.defaultJsonDecoder

  implicit def decoders[F[_]: Sync, A: Decoder]: EntityDecoder[F, A] = jsonOf[F, A]

  implicit class EncoderOpz[A](val wrappedEncodeable: A) {
    final def asJson(implicit encoder: Encoder[A]): Json = encoder(wrappedEncodeable)
    final def asJsonObject(implicit encoder: ObjectEncoder[A]): JsonObject =
      encoder.encodeObject(wrappedEncodeable)
  }
}
