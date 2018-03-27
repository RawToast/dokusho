package object dokusho  {

  case class UserReadingHistory(userId: String, readingHistory: ReadingHistory)

  case class ReadingHistory(days: Seq[Day])

  case class Day(date: String, entries: Seq[Entry])

  case class Entry(id: Long, kind: PageType, value: Int)

  case class NewEntry(kind: PageType, value: Int)

  sealed trait PageType

  case object Book extends PageType
  case object Lyric extends PageType
  case object Manga extends PageType
  case object Net extends PageType
  case object News extends PageType

  object PageType {
    import io.circe.{Encoder, Decoder}
    import io.circe.generic.extras.semiauto.{deriveEnumerationEncoder, deriveEnumerationDecoder}

    implicit def pageTypeEncoder: Encoder[PageType] = deriveEnumerationEncoder[PageType]
    implicit def pageTypeDecoder: Decoder[PageType] = deriveEnumerationDecoder[PageType]
  }
}
