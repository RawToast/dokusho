eval $(minikube docker-env)

docker build ./ -t dokusho:web