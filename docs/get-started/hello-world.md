---
layout: page
parent: Get started
title: Hello World example
nav_order: 3
---

# Hello world example

### ACAP Native SDK
Create your first ACAP application from the [Hello World](https://github.com/AxisCommunications/acap-native-sdk-examples/tree/master/hello-world) example on Github which is a part of the [ACAP Native SDK examples](https://github.com/AxisCommunications/acap-native-sdk-examples).

### ACAP Computer Vision SDK

#### Create a Hello World application
This example demonstrates how to create a simple Python application using the ACAP Computer Vision SDK and run it on an edge device.

Going from zero to a Python application running on an AXIS device is quite easy. First, the application script is written, as in the hello-world script. Next, the Dockerfile, which specifies the build of the the application image, is constructed. This needs to pull in packages from the ACAP Computer Vision SDK, as is done using the `COPY` commands. Finally, the application needs to be built and uploaded, as is specified below. It is recommended that the docker-acap on the camera has TLS authentication activated, especially if the camera is connected to an insecure or public network.

##### Requirements
To ensure compatibility with this example, the following requirements shall be met:
* Camera: ARTPEC-7 DLPU devices (e.g., Q1615 MkIII)
* docker-compose version 1.29 or higher
* Docker version 20.10.8 or higher
* Firmware: 10.7
* [docker-acap](https://hub.docker.com/r/axisecp/docker-acap) installed on the camera
* docker-acap set to use TLS (recommended) and external memory card, see [documentation](https://github.com/AxisCommunications/docker-acap)

##### Creating the application
The first step in the creation of the application is the application script. In the case of this hello-world application, it is kept very simple, as seen in `simply_hello.py` below:

**simply_hello.py**
```python
def greet_world():
    print('Hello World!')

if __name__ == '__main__':
    greet_world()
```

With the application written, the application image needs to be defined. This is defined as a Dockerfile and specifies what is uploaded and run on the camera. In this Dockerfile, the ACAP Computer Vision SDK is pulled, a runtime image of the `arm32v7` platform is created and the Python package is copied from the SDK to the runtime image. Finally, the application script that was defined earlier is copied to the image and the image's default command specified.

**Dockerfile**
```Dockerfile
ARG ARCH=armv7hf
ARG SDK_VERSION=latest
ARG REPO=axisecp
ARG RUNTIME_IMAGE=arm32v7/ubuntu:20.04

# Specify which ACAP Computer Vision SDK to use
FROM $REPO/acap-computer-vision-sdk:$SDK_VERSION-$ARCH AS cv-sdk

# Define the runtime image
FROM ${RUNTIME_IMAGE}

# Get the Python package from the CV SDK
COPY --from=cv-sdk /axis/python /

WORKDIR /app
COPY app/* /app
CMD ["python3", "simply_hello.py"]
```


##### Running the application
The first thing to do is to setup the environment. Generally, the variables described here can mostly be set to the default value, i.e., as seen below. However, the `AXIS_TARGET_IP` needs to be changed to your device's IP.

```sh
# Set environment variables
# The AXIS_TARGET_IP variable needs to be changed to your device's IP
# REPO defines where to get the ACAP Computer Vision SDK
# ARCH defines what architecture to use (e.g., armv7hf, aarch64)
# RUNTIME_IMAGE defines what base image should be used for the application image
export REPO=axisecp
export ARCH=armv7hf
export RUNTIME_IMAGE=arm32v7/ubuntu:20.04
export APP_NAME=hello-world
export AXIS_TARGET_IP=<actual camera IP address>
```

With the environment setup, the `hello-world` image can be built. The environment variables are supplied as build arguments such that they are made available to docker during the build process:

```sh
docker build . -t $APP_NAME --build-arg REPO --build-arg ARCH --build-arg RUNTIME_IMAGE
```

Next, the built image needs to be uploaded to the device. This can be done through a registry or directly. In this case, the direct transfer is used by piping the compressed application directly to the device's docker client:

```sh
# If TLS activated:
docker save $APP_NAME | docker --tlsverify -H tcp://$AXIS_TARGET_IP:2376 load

# If TLS not activated:
docker save $APP_NAME | docker -H tcp://$AXIS_TARGET_IP load
```

With the application image on the device, it can be started. As this example does not use e.g., OpenCV, no special mounts are needed, making the run command very simple:

```sh
# If TLS activated:
docker --tlsverify -H tcp://$AXIS_TARGET_IP:2376 run -it $APP_NAME

# If TLS not activated:
docker -H tcp://$AXIS_TARGET_IP run -it $APP_NAME
```

The expected output from the application is simply:

```sh
Hello World!
```

