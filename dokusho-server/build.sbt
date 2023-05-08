name := "dokusho-server"

Compile / run / mainClass := Some("Main")

val Scala3Version = "3.2.2"

val Http4sVersion = "0.23.6"
val LogbackVersion = "1.2.6"
val EdoMataVersion = "0.9.0"
val CirceVersion = "0.14.3"
val SkunkVersion = "0.5.1"
val MonocleVersion = "3.1.0"
val CatsEffect = "3.4.5"
val CatsVersion = "2.9.0"
val Redis4CatsVersion = "1.4.0"

val MunitVersion = "0.7.29"
val MunitCatsEffectVersion = "1.0.7"

resolvers ++= Resolver.sonatypeOssRepos("releases")
resolvers ++= Resolver.sonatypeOssRepos("snapshots")
resolvers += "Bintary JCenter" at "https://jcenter.bintray.com"

ThisBuild / scalaVersion := Scala3Version

libraryDependencies ++= Seq(
  // Http4s server
  "org.http4s" %% "http4s-ember-server" % Http4sVersion,
  "org.http4s" %% "http4s-ember-client" % Http4sVersion,
  "org.http4s" %% "http4s-circe" % Http4sVersion,
  "org.http4s" %% "http4s-dsl" % Http4sVersion,

  // Database
  "org.tpolecat" %% "skunk-core" % SkunkVersion,

  // Circe (Json)
  "io.circe" %% "circe-core" % CirceVersion,
  "io.circe" %% "circe-literal" % CirceVersion,
  "io.circe" %% "circe-generic" % CirceVersion,
  "io.circe" %% "circe-parser" % CirceVersion,

  // Redis
  "dev.profunktor" %% "redis4cats-streams" % Redis4CatsVersion,

  // Monocle lenses
  "dev.optics" %% "monocle-core" % MonocleVersion,
  "dev.optics" %% "monocle-macro" % MonocleVersion,

  // Logging
  "ch.qos.logback" % "logback-classic" % LogbackVersion,
  "dev.profunktor" %% "redis4cats-log4cats" % Redis4CatsVersion,

  // Test
  "org.scalameta" %% "munit" % MunitVersion % Test,
  "org.typelevel" %% "munit-cats-effect-3" % MunitCatsEffectVersion % Test
)
