name := "dokusho-server"

mainClass in(Compile, run) := Some("Main")

val SCALA_VERSION = "2.12.4"
val FINCH_VERSION = "0.17.0"
val CIRCE_VERSION = "0.8.0"
val HTTP4S_VERSION = "0.17.0"
val MONGO_VERSION = "2.1.0"

resolvers ++= Seq(
  Resolver.sonatypeRepo("releases"),
  Resolver.sonatypeRepo("snapshots"),
  "Bintary JCenter" at "http://jcenter.bintray.com"
)

def http4s = Seq(
  "org.http4s" %% "http4s-dsl" % HTTP4S_VERSION,
  "org.http4s" %% "http4s-blaze-server" % HTTP4S_VERSION,
  "org.http4s" %% "http4s-blaze-client" % HTTP4S_VERSION,
  "org.http4s" %% "http4s-circe" % HTTP4S_VERSION)

libraryDependencies ++= Seq(
  "com.github.finagle" %% "finch-core" % FINCH_VERSION,
  "com.github.finagle" %% "finch-circe" % FINCH_VERSION,
  "io.circe" %% "circe-generic" % CIRCE_VERSION,
  "org.mongodb.scala" %% "mongo-scala-driver" % MONGO_VERSION
) ++ http4s