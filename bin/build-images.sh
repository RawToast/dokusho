#!/bin/bash

eval $(minikube docker-env)

# docker build ../dokusho -t gcr.io/dokusho-199010/dokusho-web

docker build ../dokusho-server -t gcr.io/dokusho-199010/dokusho-server