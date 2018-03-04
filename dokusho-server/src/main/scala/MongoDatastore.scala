import java.util.UUID

import cats.effect._
import io.circe.generic.auto._
import io.circe.parser._
import io.circe.syntax._
import io.circe.{DecodingFailure, Json, ParsingFailure}
import org.bson.Document
import org.mongodb.scala.model.Filters._
import org.mongodb.scala.{MongoClient, MongoCollection, Observable, model}

import scala.concurrent.ExecutionContext

case class UserReadingHistory(userId: String, readingHistory: ReadingHistory)

case class ReadingHistory(days: Seq[Day])

case class Day(date: String, entries: Seq[Entry])

case class Entry(id: Long, kind: PageType, value: Int)

sealed trait PageType

case object Book extends PageType

case object Lyric extends PageType

case object Manga extends PageType

case object Net extends PageType

case object News extends PageType

class MongoDatastore(connectionString: String, databaseName: String, collectionName: String) {

  implicit val executionContext: ExecutionContext = scala.concurrent.ExecutionContext.Implicits.global

  lazy val collection: MongoCollection[Document] =
    MongoClient(connectionString)
      .getDatabase(databaseName)
      .getCollection(collectionName)

  def get(id: UUID) = for {
    document <- getDocument(id)
    hs <- toUserReadingHistory(document)
  } yield hs

  def put(g: UserReadingHistory): IO[UserReadingHistory] =
    collection.replaceOne(equal("uuid", g.userId.toString), Document.parse(g.asJson.spaces2),
      model.UpdateOptions().upsert(true)).asIO
      .map(_ => g)


  private def getDocument(id: UUID): IO[Document] = collection.find(equal("uuid", id.toString)).asIO

  private def toUserReadingHistory(task: Document): IO[UserReadingHistory] = {
    for {
      json <- parseJson(task.toJson)
      readingHistory <- parseReadingHistory(json)
    } yield readingHistory
  }

  private def parseJson(s: String): IO[Json] = parse(s) match {
    case Left(err: ParsingFailure) => IO.raiseError(err.underlying)
    case Right(json) => IO.pure(json)
  }

  private def parseReadingHistory(j: Json): IO[UserReadingHistory] = j.as[UserReadingHistory] match {
    case Left(err: DecodingFailure) => IO.raiseError(err.getCause)
    case Right(json: UserReadingHistory) => IO.pure(json)
  }

  private implicit class IOSyntax[T](obs: Observable[T]) {
    def asIO: IO[T] = IO.fromFuture(IO(obs.head()))

    def asSeqIO: IO[Seq[T]] = IO.fromFuture(IO(obs.toFuture()))
  }

}