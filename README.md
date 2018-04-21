# Dokusho

[T1]: https://travis-matrix-badges.herokuapp.com/repos/RawToast/dokusho/branches/master/1
[T2]: https://travis-matrix-badges.herokuapp.com/repos/RawToast/dokusho/branches/master/2
[TR]: https://travis-ci.org/RawToast/dokusho

[C1]: https://coveralls.io/repos/github/RawToast/dokusho/badge.svg
[CR]: https://coveralls.io/github/RawToast/dokusho

| [Dokusho](dokusho/)   | [Dokusho Server](dokusho-server/)|
|-----------------------|---------------------|
| [![Travis][T1]][TR]   | [![Travis][T2]][TR] |
| [![Coveralls][C1]][CR]|                     |


Japanese reading page count calculator, using similar page values as the [Tadoku reading contest](http://readmod.com).

読書 (dokusho)

Noun, Suru verb

1. reading

## Running the project

This is a multi-module project. See the relevent modules for running instructions.

### Minikube

This project is built with Kubernetes for Google Cloud Engine; however, [Minikube](https://github.com/kubernetes/minikube) can be used to run a local backend cluster. 

* `minikube start --vm-driver <hyperkit, xhyve, virtualbox, etc>`
* `./bin/build-images.sh`
* `./bin/create-services.sh`

The backend's location can then be found using: `minikube service backend --url`.

### CORS

CORS headers are not set so to use the frontend CORS protection needs to be disabled. On Mac OS Chrome can be started as follows: `open -a Google\ Chrome --args --disable-web-security --user-data-dir`


## Additional Information

This project was bootstrapped with [Create React App](https://github.com/facebookincubator/create-react-app).

* [ReasonML](https://reasonml.github.io/)
* [Reason React](https://reasonml.github.io/reason-react/)
* [Scala](http://scala-lang.org)
* [Http4s](http://http4s.org)
* [Kubernetes](https://kubernetes.io)
* [Minikube](https://github.com/kubernetes/minikube)
* [MongoDB](https://www.mongodb.com)
* [Auth0](https://www.auth0.com)
