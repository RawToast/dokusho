name := "dokusho-server"

mainClass in(Compile, run) := Some("Main")

val SCALA_VERSION = "2.12.4"
val CIRCE_VERSION = "0.9.1"
val HTTP4S_VERSION = "0.18.1"
val MONGO_VERSION = "2.2.1"

resolvers ++= Seq(
  Resolver.sonatypeRepo("releases"),
  Resolver.sonatypeRepo("snapshots"),
  "Bintary JCenter" at "http://jcenter.bintray.com"
)

libraryDependencies ++= Seq(
  "org.http4s" %% "http4s-dsl" % HTTP4S_VERSION,
  "org.http4s" %% "http4s-blaze-server" % HTTP4S_VERSION,
//  "org.http4s" %% "http4s-blaze-client" % HTTP4S_VERSION,
  "org.http4s" %% "http4s-circe" % HTTP4S_VERSION,

  "io.circe" %% "circe-generic" % CIRCE_VERSION,
  "io.circe" %% "circe-parser" % CIRCE_VERSION,

  "org.mongodb.scala" %% "mongo-scala-driver" % MONGO_VERSION,

  "ch.qos.logback" % "logback-classic" % "1.2.3"
)

scalacOptions ++= Seq("-Ypartial-unification")