# Dokusho 

[![Build Status](https://travis-matrix-badges.herokuapp.com/repos/RawToast/dokusho/branches/master/1)](https://travis-ci.org/RawToast/dokusho)
[![Coverage Status](https://coveralls.io/repos/github/RawToast/dokusho/badge.svg)](https://coveralls.io/github/RawToast/dokusho)

A Japanese reading page count calculator, using the same page values as the [Tadoku reading contest](http://readmod.com).

読書 (dokusho)

Noun, Suru verb

1. reading

## Running the frontend

### Using npm / yarn

As this project is built using ReasonML, it requires the bucklescript platform to compile and run. To start the application on a fresh machine run the following commands to start a server at `localhost:3000`:

* `npm install -g bs-platform`
* `yarn`
* `yarn start`

### Docker

Alternatively, docker can be used to run the project. The service will be available at: `localhost:80`

* `./run-docker.sh`

## Additional Information

This project was bootstrapped with [Create React App](https://github.com/facebookincubator/create-react-app).

* [ReasonML](https://reasonml.github.io/)
* [Reason Scripts](https://github.com/reasonml-community/reason-scripts)
* [Reason React](https://reasonml.github.io/reason-react/)
* [Rationale](https://github.com/jonlaing/rationale)
* [Bs-Jest](https://github.com/glennsl/bs-jest)
