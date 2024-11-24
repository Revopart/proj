cd ..
echo "Directory after moving:"
pwd
docker rmi -f school21/lest:1.0
docker build . -t school21/lest:1.0 -f Docker/Dockerfile
docker run -it school21/lest:1.0