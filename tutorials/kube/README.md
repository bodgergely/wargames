minikube ssh - to log in
minikube tunnel - to enable LoadBalancer be available. This is how we can export Services
minikube dashboard - UI for Kubernetes

alias k=kubectl

k get svc
k get pods
k get replicationcontrollers
k describe pods
k cluster-info
kubectl run kubia --image=bodgergely/kubia --port=8080 --generator=run/v1
kubectl expose rc kubia --type=LoadBalancer --name kubia-http
kubectl scale rc kubia --replicas=3 - to scale to 3 three instances
kubectl port-forward kubia-manual 8888:8080



