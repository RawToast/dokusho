name := "dokusho-server"

mainClass in(Compile, run) := Some("Main")

val SCALA_VERSION = "2.12.4"
val FINCH_VERSION = "0.17.0"
val CIRCE_VERSION = "0.8.0"

resolvers ++= Seq(
  Resolver.sonatypeRepo("releases"),
  Resolver.sonatypeRepo("snapshots"),
  "Bintary JCenter" at "http://jcenter.bintray.com"
)

libraryDependencies ++= Seq(
  "com.github.finagle" %% "finch-core" % FINCH_VERSION,
  "com.github.finagle" %% "finch-circe" % FINCH_VERSION,
  "io.circe" %% "circe-generic" % CIRCE_VERSION
)