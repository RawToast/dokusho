#!/bin/bash

echo !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
echo !!! This script expects Hyperkit drivers to be installed !!!
echo !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

minikube start --vm-driver hyperkit

cd bin

./build-images.sh

./create-services.sh