package chousen.api.core

import java.util.UUID

import fs2.{Strategy, Task}
import io.circe.{DecodingFailure, Json, ParsingFailure}
import io.circe.generic.auto._
import io.circe.parser._
import io.circe.syntax._
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

 implicit val strategy: Strategy = Strategy.fromExecutionContext(executionContext)

 lazy val collection: MongoCollection[Document] =
   MongoClient(connectionString)
     .getDatabase(databaseName)
     .getCollection(collectionName)

 def get(id :UUID) = for {
   document <- getDocument(id)
   hs <- toGameState(document)
 } yield hs

 def put(g: T): Task[T] =
   collection.replaceOne(equal("uuid", g.uuid.toString), Document.parse(g.asJson.spaces2),
     model.UpdateOptions().upsert(true)).asTask
     .map(_ => g)


 private def getDocument(id: UUID): Task[Document] = collection.find(equal("uuid", id.toString)).asTask

 private def toGameState(task: Document): Task[GameState] = {
   for {
     json <- parseJson(task.toJson)
     gameState <- parseGameState(json)
   } yield gameState
 }

 private def parseJson(s: String): Task[Json] = parse(s) match {
   case Left(err:ParsingFailure) => Task.fail(err.underlying)
   case Right(json) => Task.now(json)
 }

 private def parseGameState(j : Json): Task[GameState] = j.as[GameState] match {
   case Left(err: DecodingFailure) => Task.fail(err.getCause)
   case Right(json: GameState) => Task.now(json)
 }

 private implicit class TaskSyntax[T](obs: Observable[T]) {
   def asTask: Task[T] = Task.fromFuture(obs.head())
 }
}