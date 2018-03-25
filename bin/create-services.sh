#!/bin/bash

kubectl create -f  ../kube/mongo-service.yaml
kubectl create -f  ../kube/backend-service.yaml

kubectl create -f  ../kube/mongo-controller.yaml
kubectl create -f  ../kube/backend-controller.yaml
