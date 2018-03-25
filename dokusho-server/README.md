# Dokusho-Server

[![Build Status](https://travis-matrix-badges.herokuapp.com/repos/RawToast/dokusho/branches/master/2)](https://travis-ci.org/RawToast/dokusho)

Throwaway backend server for Dokusho. This is a work in progress service for experimenting and empowering frontend development.

Once the frontend reaches a reasonable level of functionality, this backend service will be revisited.

## Running the backend

### Using sbt

`sbt run` will compile and start a server listening on `8080` 

### Endpoints

* Fetch the reading history for a user
  * GET `/user/<userID>`
* Replace a user's reading history
  * PUT `user/<userID>` 
* Add a new entry to the user's reading history
  * POST  `user/<userID>/add`


## Additional Information

This project is built using the following:

* [Scala](http://scala-lang.org)
* [Cats](https://typelevel.org/cats)
* [Http4s](http://http4s.org)
* [Circe](https://circe.github.io/circe/)
