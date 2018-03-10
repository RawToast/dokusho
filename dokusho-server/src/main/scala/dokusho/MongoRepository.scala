package dokusho

import cats.effect._
import io.circe.generic.auto._
import io.circe.parser._
import io.circe.syntax._
import io.circe.{DecodingFailure, Json, ParsingFailure}
import monocle.macros.GenLens
import org.bson.Document
import org.mongodb.scala.model.Filters._
import org.mongodb.scala.{MongoClient, MongoCollection, Observable, model}

import scala.concurrent.ExecutionContext

class MongoRepository(connectionString: String, databaseName: String, collectionName: String) {

  implicit val executionContext: ExecutionContext = scala.concurrent.ExecutionContext.Implicits.global

  lazy val collection: MongoCollection[Document] =
    MongoClient(connectionString)
      .getDatabase(databaseName)
      .getCollection(collectionName)

  def get(userId: String) = for {
    document <- getDocument(userId)
    hs <- toUserReadingHistory(document)
  } yield hs

  def put(g: UserReadingHistory): IO[UserReadingHistory] =
    collection.replaceOne(equal("uuid", g.userId.toString), Document.parse(g.asJson.spaces2),
      model.UpdateOptions().upsert(true)).asIO
      .map(_ => g)

  // Slow, inefficient method.
  def addEntry(userId: String, date: String, entry: Entry) = {
    for {
      urh <- get(userId)
      days = urh.readingHistory.days
      dayToUpdate = days.find(_.date == userId).getOrElse(Day(date, Seq.empty))
      updatedDay = dayToUpdate.copy(entries = dayToUpdate.entries :+ entry)
      doc = daysLens.modify(upsertDay(updatedDay))(urh)
    } yield doc
  }
  val daysLens = GenLens[UserReadingHistory](_.readingHistory.days)

  def upsertDay(day:Day)(days: Seq[Day]): Seq[Day] =
    if(days.exists(d => d.date == day.date)){
      days.withFilter(d => d.date == day.date)
          .map(d => day)



    } else {
     days :+ day
    }



  private def getDocument(id: String): IO[Document] = collection.find(equal("userId", id)).asIO

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