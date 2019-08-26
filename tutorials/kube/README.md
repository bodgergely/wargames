minikube ssh - to log in
minikube tunnel - to enable LoadBalancer be available. This is how we can export Services
minikube dashboard - UI for Kubernetes

k get svc
k get pods
k cluster-info
kubectl run kubia --image=bodgergely/kubia --port=8080 --generator=run/v1
kubectl expose rc kubia --type=LoadBalancer --name kubia-http

