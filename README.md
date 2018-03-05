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

### Building

As this project is built using ReasonML, it requires the bucklescript platform to compile and run. To start the application on a fresh machine run the following commands to start a server at `localhost:3000`:

* `npm install -g bs-platform`
* `yarn`
* `yarn start`

### Minikube

[Minikube](https://github.com/kubernetes/minikube) can be used to run a local kubernetes cluster with a Mongo instance. The url can be found using: `minikube service web --url`

* `minikube start --vm-driver <hyperkit, xhyve, virtualbox, etc>`
* `./kube/build-image.sh`
* `./kube/run-local.sh`

## Additional Information

This project was bootstrapped with [Create React App](https://github.com/facebookincubator/create-react-app).

* [ReasonML](https://reasonml.github.io/)
* [Reason Scripts](https://github.com/reasonml-community/reason-scripts)
* [Reason React](https://reasonml.github.io/reason-react/)
* [Rationale](https://github.com/jonlaing/rationale)
* [Bs-Jest](https://github.com/glennsl/bs-jest)
* [Scala](http://scala-lang.org)
* [Finch](https://finagle.github.io/finch/)
* [Circe](https://circe.github.io/circe/)
* [Kubernetes](https://kubernetes.io)
* [Minikube](https://github.com/kubernetes/minikube)
* [MongoDB](https://www.mongodb.com)
