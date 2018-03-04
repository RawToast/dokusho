#!/bin/bash 

docker build ./ -t dokusho

docker run -p 3000:3000 node:dokusho