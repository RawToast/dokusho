#!/bin/bash

eval $(minikube docker-env)

docker build ../dokusho -t dokusho:web

docker build ../dokusho-server -t dokusho:server