---
layout: page
title: Develop applications / Efficient programming
---
## Application project structure
TBD

## Build, install, run

### Native SDK

To build, install and run an ACAP application, use the image in the [axisecp/acap-sdk](https://hub.docker.com/r/axisecp/acap-sdk) repository. You can use this image in two ways:

* As a base image to build a custom application builder image, see [Build, install and run with custom application image](#build-install-and-run-with-custom-application-image).
* Interactively inside the container, see [Build, install and run interactively inside container](#build-install-and-run-with-custom-application-image).

To build an application defined by manifest.json, use the acap-build tool, see [Build tool](#build-tool).

To build an application defined by package.conf, use the create-package.sh build script, see [Build script](#build-script).

#### Build script
For applications defined by `package.conf`, use the build script `create-package.sh`.

The script does the following:

* Checks that the file `package.conf` exists and does not contain any errors.
* Asks for missing or invalid parameters and creates `package.conf`.
* Executes make in the current directory to compile the application source code into an application binary file.
* Creates an **eap** (embedded application package) package including the application binary, html files (if any) and configuration files.
* Creates a copy of `LICENSE` file.

The created application package filename has the following format:

```
<PACKAGENAME>_<APPMAJORVERSION>_<APPMINORVERSION>_<APPMICROVERSION>_<SDK_ARCHITECTURE>.eap
```

The created copy of `LICENSE` filename has the following format:

```
<PACKAGENAME>_<APPMAJORVERSION>_<APPMINORVERSION>_<APPMICROVERSION>_LICENSE.txt
```

#### Build tool
For applications defined by **manifest.json**, use the build tool **acap-build**.

The acap-build tool does the following:

* Runs make, performing any required cross-compilation as defined in the available Makefile.
* Validates the manifest file against the manifest schema.
* Generates a package.conf file and related configuration files for backward compatibility.
* Creates an EAP file including:
    * application executable
    * LICENSE file
    * any available html and lib folder
    * other files listed in the acap-build request
    * generated backward compatibility files

For help on using the build tool, run `acap-build -h`.

> * If any additional files were previously listed in **OTHERFILES** in the **package.conf** file, these need to be listed as input to the acap-build command using the flag -a, for example `acap-build ./ -a file1 -a file2`.
> * At some point an EAP will be required to be based on a manifest file instead of a **package.conf** file. For such an ACAP application package to be supported in older firmware, a **package.conf** file is generated and included in the EAP file. Although it’s the manifest file that is the base setup file for the ACAP application when building an EAP package in the SDK.
> * In the next step of introducing manifest file EAP files, systemd will start and stop the ACAP application. It then assumes execution failure if the main process dies, which means that the process must not fork off to a background process.

#### Build, install and run with custom application image
For instructions on how to set up your build, to install, and to run with custom application image, use the **Hello World** application example shown in [Set up and verify the SDK](#set-up-and-verify-the-sdk).

Using the custom application image, all the building and packaging is done inside a Docker container. The application is then copied to a custom directory, meaning that the original application project directory is not changed.

The top structure for an ACAP application contains a Dockerfile and a directory called `app` where the application project files are placed.

To install, start, stop and remove the application, use the device’s web interface.

#### Build, install and run interactively inside container
To be able to work interactively with your application, you can bind mount the application project directory into the container. In this way, you can build and package the application directly in this folder. You may also install, start, stop and remove the application on a device directly from inside the container.

The top structure for an ACAP application contains a directory called, for example `app` where the application project files are placed.

To run the acap-sdk container interactively and mount the application project, go to the directory that contains `app` and run:

```
docker run -v $PWD/app:/opt/app --rm -i -t axisecp/acap-sdk:3.3-armv7hf-ubuntu20.04
```
where:

* `axisecp/acap-sdk` is the Docker hub repostitory
* `3.3-armv7hf-ubuntu20.04` is the tag that points out which SDK version and architecture to use
* `-v $PWD/app:/opt/app` mounts the host directory `$PWD/app` into the container directory `/opt/app`
* `--rm` removes the container after closing it
* `-i` is to run the container interactively
* `-t` which repository tag to use

You should end up in a container with a prompt similar to:

```
root@1e6b4f3d5a2c:/opt/app#
```

Now you’re ready to build and install the application. See [Build the application](#build-the-application), and [Install the application](#install-the-application)

> The bind mount means that any changes made inside the container on /opt/app will be made to the host directory `$PWD/app`.

**Build the application**

**Using package.conf (ACAP SDK version 3.2 and earlier)**

To build an application stand in the application directory inside the container and run `create-package.sh`.

**Using manifest.json (ACAP SDK version 3.3 and later)**

To build an application, stand in the application directory inside the container and run the **acap-build** tool.

**Install the application**

The SDK helps with installing a built application on the device from a terminal. You can also install application packages, using the device's web interface. But this method is less convenient during application development.

To install a built application on a device, run:
```
eap-install.sh
```
Run the command without any options to get help.

To install a built application on a device, run the following command (you must enter the IP address and the root password of the device the first time):
```
eap-install.sh <device-ip> <password> install
eap-install.sh 192.168.0.90 pass install
```
The command remembers the device-ip and password after the first successful execution. After this you can simply run:
```
eap-install.sh install
```
> You must run the command from the application project directory, see [Application project structure](#application-project-structure).

**Start, stop, and remove the application**

Before you continue, make sure that you have done a first successful execution of shell script command `eap-install.sh`, see [Install the application](#install-the-application) for more information.

To start, stop and remove an installed application, run:
```
eap-install.sh [start|stop|remove]
```
To start an installed application on the device, run:
```
eap-install.sh start
```
Now you can see the status of the application using the device's web interface.

To stop a running application, run:
```
eap-install.sh stop
```
To remove an installed application, run:
```
eap-install.sh remove
```

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