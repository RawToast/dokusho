package dokusho

import cats.data.OptionT
import cats.effect.IO
import io.circe.generic.auto._
import io.circe.parser._
import io.circe.syntax._
import io.circe.{DecodingFailure, Json, ParsingFailure}
import monocle.macros.GenLens
import org.bson.Document
import org.mongodb.scala.model.Filters._
import org.mongodb.scala.{FindObservable, MongoClient, MongoCollection, Observable, model}

import scala.concurrent.ExecutionContext

class MongoRepository(connectionString: String, databaseName: String, collectionName: String) {

  private lazy val daysLens = GenLens[UserReadingHistory](_.readingHistory.days)
  private lazy val entriesLens = GenLens[Day](_.entries)

  implicit val executionContext: ExecutionContext = scala.concurrent.ExecutionContext.Implicits.global

  private lazy val collection: MongoCollection[Document] =
    MongoClient(connectionString)
      .getDatabase(databaseName)
      .getCollection(collectionName)

  def get(userId: String): IO[Option[UserReadingHistory]] =
    OptionT(getDocumentIoOpt(userId))
      .semiflatMap(toUserReadingHistory)
      .value


  def getUnsafe(userId: String): IO[UserReadingHistory] =
    getDocumentIO(userId)
      .flatMap(toUserReadingHistory)

  def put(g: UserReadingHistory): IO[UserReadingHistory] =
    collection.replaceOne(equal("userId", g.userId), Document.parse(g.asJson.spaces2),
      model.UpdateOptions().upsert(true)).asIO
      .map(_ => g)

  def addEntry(userId: String, date: String, entry: Entry): IO[UserReadingHistory] = {
    for {
      urh <- getUnsafe(userId)
      days = urh.readingHistory.days
      dayToUpdate = days.find(_.date == date).getOrElse(Day(date, Seq.empty))
      updatedDay = entriesLens.modify(_ :+ entry)(dayToUpdate)
      doc = daysLens.modify(upsertDay(updatedDay))(urh)
    } yield doc
  }

  private def upsertDay(day: Day)(days: Seq[Day]): Seq[Day] =
    if (days.exists(_.date == day.date)) {
      days.withFilter(_.date == day.date)
        .map(_ => day)
    } else {
      days :+ day
    }

  private def getDocument(id: String): FindObservable[Document] = collection.find(equal("userId", id))

  private def getDocumentIO(id: String): IO[Document] = getDocument(id).asIO

  private def getDocumentIoOpt(id: String): IO[Option[Document]] = getDocument(id).asIOOpt

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

    def asIOOpt: IO[Option[T]] = IO.fromFuture(IO(obs.headOption()))

    def asSeqIO: IO[Seq[T]] = IO.fromFuture(IO(obs.toFuture()))
  }

}