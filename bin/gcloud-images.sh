#!/bin/bash

docker build ../dokusho -t gcr.io/dokusho-199010/dokusho-web

docker build ../dokusho-server -t gcr.io/dokusho-199010/dokusho-server

gcloud docker -- push gcr.io/dokusho-199010/dokusho-web:latest

gcloud docker -- push gcr.io/dokusho-199010/dokusho-server:latest