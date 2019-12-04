name := "dokusho-server"

mainClass in(Compile, run) := Some("Main")

val SCALA_VERSION = "2.13.1"

val CIRCE_VERSION = "0.12.2"
val HTTP4S_VERSION = "0.21.0-M6"
val KIND_PROJECTOR_VERSION = "0.11.0"
val MONGO_VERSION = "2.7.0"
val MONOCLE_VERSION = "2.0.0"

scalaVersion := SCALA_VERSION

resolvers ++= Seq(
  Resolver.sonatypeRepo("releases"),
  Resolver.sonatypeRepo("snapshots"),
  "Bintary JCenter" at "https://jcenter.bintray.com"
)

libraryDependencies ++= Seq(
  "org.http4s" %% "http4s-dsl" % HTTP4S_VERSION,
  "org.http4s" %% "http4s-blaze-server" % HTTP4S_VERSION,
  "org.http4s" %% "http4s-circe" % HTTP4S_VERSION,
  "org.http4s" %% "http4s-blaze-client" % HTTP4S_VERSION,

  "io.circe" %% "circe-generic" % CIRCE_VERSION,
  "io.circe" %% "circe-generic-extras" % CIRCE_VERSION,
  "io.circe" %% "circe-parser" % CIRCE_VERSION,

  "org.mongodb.scala" %% "mongo-scala-drhttpiver" % MONGO_VERSION,

  "ch.qos.logback" % "logback-classic" % "1.2.3",

  "com.github.julien-truffaut" %%  "monocle-core"  % MONOCLE_VERSION,
  "com.github.julien-truffaut" %%  "monocle-macro" % MONOCLE_VERSION,

//  "org.spire-math"  %% "kind-projector" % KIND_PROJECTOR_VERSION,

  "org.scalatest" % "scalatest_2.12" % "3.0.5" % Test
)
