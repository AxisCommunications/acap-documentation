---
layout: page
parent: Develop ACAP applications
title: Build, install, run
nav_order: 3
redirect_to: https://developer.axis.com/acap/develop/build-install-run
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
- Creates an EAP (Embedded Application Package) file with suffix `.eap` including:
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
>   command using the flag -a, for example `acap-build . -a file1 -a file2`.
> - For the ACAP application package to be supported in older AXIS OS, a
> **package.conf** file is generated and included in the EAP file. Although it’s
>   the manifest file that is the base setup file for the ACAP application when
>   building an EAP package in the SDK.
> - Systemd will start and stop the ACAP application. It then assumes execution
>   failure if the main process dies, which means that the process must not fork
>   off to a background process.

### Build, install and run with custom application image

For instructions on how to set up your build, to install, and to run with custom
application image, use the
[Hello World](https://github.com/AxisCommunications/acap-native-sdk-examples/tree/main/hello-world)
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

To install a built application on a device, run the following command (you must enter the IP address and username and password of the device the first time):

```bash
eap-install.sh <axis_device_ip> <admin_account> <password> install
eap-install.sh 192.168.0.90 admin-user admin-password install
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
