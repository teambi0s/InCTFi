# Issues with Debugging

In case you encounter issues with loading libraries, you might want to fire up your ubuntu 20.04 Virtual Machine or completely shift to Docker for Dynamic Debugging purposes.

If you wish to use docker , then here are the instructions to set it up

### Setting up Docker env

The Dockerfile has been provided along with the other handout files.

All you have to do is build and run the container.

```sh
sudo docker build -t container .
sudo docker run -dit --privileged container 
sudo docker ps
```

Take the ID of container and ->

```sh
sudo docker exec -it <ID> /bin/bash
```

Most of the utilities to debug properly have been installed already , feel free to update the Dockerfile according to your needs.

Happy Hacking :)
