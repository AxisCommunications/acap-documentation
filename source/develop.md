---
layout: page
title: Develop applications / Efficient programming
---
## Application project structure

## Build, install, run

### Native SDK
TBD

### CV SDK inkl. Docker ACAP

#### Build
The applications are built using the Docker framework which means that building is not always necessary. It's only necessary if your application uses custom images which are not readily available. The Computer Vision functionality can be accessed by basing your image on the [ACAP Computer Vision SDK](https://hub.docker.com/r/axisecp/acap-computer-vision-sdk). Please see the [hello world example](#hello-world-example) for an example of how to create a custom image using the [ACAP Computer Vision SDK](https://hub.docker.com/r/axisecp/acap-computer-vision-sdk). For more information on how to build a custom docker image, see https://docs.docker.com/get-started/02_our_app/.

#### Install and run
> Installing and running ACAP4 applications requires the [Docker ACAP](https://hub.docker.com/r/axisecp/docker-acap) to be installed on the camera.

Running and installing is usually done in the same step in the docker framework by using the docker command. Note that this command shall be run from a separate host and not on the camera. The intended way to install and run applications is by supplying the docker command with the IP adress of the camera using the -H parameter. The two commands usually used for this purpose are [docker compose](https://docs.docker.com/compose/) and [docker run](https://docs.docker.com/engine/reference/run/). Below are examples of how to use these commands:
```
docker run -d -H tcp://$CAMERA_IP $IMAGE

docker compose -H tcp://$CAMERA_IP up
```

## Setting up VSCode
TBD