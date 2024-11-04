---
layout: acap_container_applications_deprecation_page
parent: Develop container applications
title: Build, install, run
nav_order: 1
---

# Build, install, run

## ACAP Computer Vision SDK incl. Docker ACAP

### Build

The applications are built using the Docker framework which means that building is not always necessary. It's only necessary if your application uses custom images which are not readily available. The Computer Vision functionality can be accessed by basing your image on the [ACAP Computer Vision SDK](https://hub.docker.com/r/axisecp/acap-computer-vision-sdk). Please see the [ACAP Computer vision SDK examples](https://github.com/AxisCommunications/acap-computer-vision-sdk-examples) for examples of how to create a custom image using the ACAP Computer Vision SDK. For more information on how to build a custom docker image, see Docker Hub's [sample application](https://docs.docker.com/get-started/02_our_app/).

### Install and run

> Installing and running container based ACAP applications requires the [Docker
> ACAP](https://github.com/AxisCommunications/docker-acap) to be installed on
> the camera. Note that the Docker ACAP is set to use TLS authentication by
> default, which means that you are required to add certificates to the camera
> before it is possible to start the ACAP (see the link above for information
> on how to do that). It is assumed that TLS authentication is activated in the examples.
> There is a setting to disable TLS authentication but please be aware that doing so is extremely insecure.

Installing and running a Docker image on an AXIS device is done using the `docker` client. The idea is to get the application image to the device and then run it remotely using the `-H` flag, which lets the docker client connect to a remote docker daemon, such as the one running on your AXIS device.

Downloading the image to the device is usually done through either a container registry or in a peer-to-peer fashion from another Docker client. The container registry option involves building your application image and then using `docker push $IMAGE_NAME` to make it available on the container registry. This image can then be pulled onto the AXIS device by running:

```sh
docker --tlsverify -H tcp://$CAMERA_IP:2376 pull $IMAGE_NAME
```

The direct approach to getting an application image onto the device is to save the image locally and pipe the result to the edge device's docker daemon:

```sh
docker save $IMAGE_NAME | docker --tlsverify -H tcp://$CAMERA_IP:2376 load
```

Once the images are on the device, they can be started remotely. This is similarly done using the `-H` flag, but with the `docker run` command, i.e., for a single application image:

```sh
docker --tlsverify -H tcp://$CAMERA_IP:2376 run $IMAGE_NAME
```

If the application has been specified using a `docker-compose.yml` file, which can be useful to preserve required environment variables, mounts and devices, `docker-compose` can be used to start the application:

```sh
docker-compose --tlsverify -H tcp://$CAMERA_IP:2376 up
```

After running `docker-compose up`, created containers, networks and volumes can be removed by:

```sh
docker-compose --tlsverify -H tcp://$CAMERA_IP:2376 down -v
```

#### Configure network proxy settings

If the device is located behind a proxy the Docker daemon needs to be configured.
Instructions can be found in the Docker ACAP repository under [Proxy Setup](https://github.com/AxisCommunications/docker-acap/tree/main?tab=readme-ov-file#proxy-setup).

## The Docker Compose ACAP

In addition to the Docker ACAP, there is another similar ACAP: the [Docker Compose ACAP](https://github.com/AxisCommunications/docker-compose-acap). The Docker Compose ACAP not only contains the Docker daemon but also the Docker client, which is why it is significantly larger. When the Docker Compose ACAP is installed, it is possible to run Docker commands directly on the camera instead of using a Docker client on another machine, as is necessary when using the regular Docker ACAP.

The main purpose of the Docker Compose ACAP is to enable running containers as part of native ACAP applications, as demonstrated in [this example](https://github.com/AxisCommunications/acap-native-sdk-examples/tree/main/container-example). This use case requires that there is a Docker client present on the camera since the ACAP itself must be able to start the containers.
