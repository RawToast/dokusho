package dokusho

import cats._

trait HistoryRepository[F[_]: Monad]:
  def get(userId: String): F[Option[UserReadingHistory]]

  def put(g: UserReadingHistory): F[Unit]

class InMemoryHistoryRepository extends HistoryRepository[Id]:
  private val store =
    scala.collection.mutable.Map.empty[String, UserReadingHistory]

  override def put(g: UserReadingHistory): Id[Unit] =
    store.put(g.userId, g) match
      case None    => ()
      case Some(_) => ()

  def get(userId: String): Id[Option[UserReadingHistory]] =
    store.get(userId)
