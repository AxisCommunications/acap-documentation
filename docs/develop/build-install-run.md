---
layout: page
parent: Develop ACAP applications
title: Build, install, run
nav_order: 3
---

# Build, install, run

## ACAP Native SDK

To build, install and run an ACAP application, use the [ACAP Native SDK](https://github.com/AxisCommunications/acap-native-sdk). You can use the ACAP Native SDK Docker image in two ways:

- As a base image to build a custom application builder image, see [Build, install and run with custom application image](#build-install-and-run-with-custom-application-image).
- Interactively inside the container, see [Build, install and run interactively inside container](#build-install-and-run-interactively-inside-container).

### Build tool

Use the **acap-build** tool to build and package your application.

The acap-build tool does the following:

- Runs make, performing any required cross-compilation as defined in the available `Makefile`.
- Validates the manifest file against the manifest schema.
- Generates a `package.conf` file and related configuration files for backward compatibility.
- Creates an EAP (Embedded Application Package) file with suffix .eap including:
  - application executable
  - `LICENSE` file
  - any available `html` and `lib` folder
  - other files listed in the `acap-build` request
  - generated backward compatibility files

For help on using the build tool, run `acap-build -h`.

> - In an older version of the ACAP framework a file named **package.conf**
>   was used for configuration. It has since been replaced by
> **manifest.json**. If any additional files were previously listed in **OTHERFILES**
>   in the package.conf file, these now need to be listed as input to the acap-build
>   command using the flag -a, for example `acap-build ./ -a file1 -a file2`.
> - For the ACAP application package to be supported in older firmware, a
> **package.conf** file is generated and included in the EAP file. Although it’s
>   the manifest file that is the base setup file for the ACAP application when
>   building an EAP package in the SDK.
> - Systemd will start and stop the ACAP application. It then assumes execution
>   failure if the main process dies, which means that the process must not fork
>   off to a background process.

### Build, install and run with custom application image

For instructions on how to set up your build, to install, and to run with custom
application image, use the
[Hello World](https://github.com/AxisCommunications/acap-native-sdk-examples/tree/master/hello-world)
example on GitHub.

Using the custom application image, all the building and packaging is done inside a Docker container. The application is then copied to a custom directory, meaning that the original application project directory is not changed.

The top structure for an ACAP application contains a Dockerfile and a directory called `app` where the application project files are placed.

To install, start, stop and remove the application, use the device’s web interface.

### Build, install and run interactively inside container

To be able to work interactively with your application, you can bind mount the application project directory into the container. In this way, you can build and package the application directly in this folder. You may also install, start, stop and remove the application on a device directly from inside the container.

The top structure for an ACAP application contains a directory called, for example `app` where the application project files are placed.

To run the acap-native-sdk container interactively and mount the application project, go to the directory that contains `app` and run:

```bash
docker run -v $PWD/app:/opt/app --rm -i -t axisecp/acap-native-sdk:1.0-armv7hf-ubuntu20.04
```

where:

- `axisecp/acap-native-sdk` is the Docker Hub repository
- `1.0-armv7hf-ubuntu20.04` is the tag that points out which SDK version and architecture to use
- `-v $PWD/app:/opt/app` mounts the host directory `$PWD/app` into the container directory `/opt/app`
- `--rm` removes the container after closing it
- `-i` is to run the container interactively
- `-t` which repository tag to use

You should end up in a container with a prompt similar to:

```bash
root@1e6b4f3d5a2c:/opt/app#
```

Now you’re ready to build and install the application. See [Build the application](#build-the-application), and [Install the application](#install-the-application)

> The bind mount means that any changes made inside the container on /opt/app
> will be made to the host directory `$PWD/app`.

#### Build the application

To build an application, stand in the application directory inside the container and run the **acap-build** tool.

#### Install the application

The SDK helps with installing a built application on the device from a terminal. You can also install application packages, using the device's web interface. But this method is less convenient during application development.

To install a built application on a device, run:

```bash
eap-install.sh
```

Run the command without any options to get help.

To install a built application on a device, run the following command (you must enter the IP address and the root password of the device the first time):

```bash
eap-install.sh <device-ip> <password> install
eap-install.sh 192.168.0.90 pass install
```

The command remembers the device-ip and password after the first successful execution. After this you can simply run:

```bash
eap-install.sh install
```

> You must run the command from the application project directory, see
> [Application project structure](application-project-structure).

#### Start, stop, and remove the application

Before you continue, make sure that you have done a first successful execution of shell script command `eap-install.sh`, see [Install the application](#install-the-application) for more information.

To start, stop and remove an installed application, run:

```bash
eap-install.sh [start|stop|remove]
```

To start an installed application on the device, run:

```bash
eap-install.sh start
```

Now you can see the status of the application using the device's web interface.

To stop a running application, run:

```bash
eap-install.sh stop
```

To remove an installed application, run:

```bash
eap-install.sh remove
```

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

## The Docker Compose ACAP

In addition to the Docker ACAP, there is another similar ACAP: the [Docker Compose ACAP](https://github.com/AxisCommunications/docker-compose-acap). The Docker Compose ACAP not only contains the Docker daemon but also the Docker client, which is why it is significantly larger. When the Docker Compose ACAP is installed, it is possible to run Docker commands directly on the camera instead of using a Docker client on another machine, as is necessary when using the regular Docker ACAP.

The main purpose of the Docker Compose ACAP is to enable running containers as part of native ACAP applications, as demonstrated in [this example](https://github.com/AxisCommunications/acap-native-sdk-examples/tree/master/container-example). This use case requires that there is a Docker client present on the camera since the ACAP itself must be able to start the containers.
