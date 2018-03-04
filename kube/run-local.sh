#!/bin/bash

kubectl create -f  kube/mongo-service.yaml
kubectl create -f  kube/web-service.yaml

kubectl create -f  kube/mongo-controller.yaml
kubectl create -f  kube/web-controller.yaml
