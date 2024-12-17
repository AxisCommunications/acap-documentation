---
layout: acap_sdk_version_3
parent: Develop applications
grand_parent: ACAP SDK version 3
title: Build, install and run the application
nav_order: 2
---
# Build, install and run the application

To build, install and run an ACAP application, use the image in the [axisecp/acap-sdk](https://hub.docker.com/r/axisecp/acap-sdk) repository. You can use this image in two ways:

- As a base image to build a custom application builder image, see [Build, install and run with custom application image](#build-install-and-run-with-custom-application-image).
- Interactively inside the container, see [Build, install and run interactively inside container](#build-install-and-run-interactively-inside-container).

To build an application defined by `manifest.json`, use the acap-build tool, see [Build tool](#build-tool).

To build an application defined by `package.conf`, use the `create-package.sh` build script, see [Build script](#build-script).

## Build script

For applications defined by `package.conf`, use the build script `create-package.sh`.

The script does the following:

- Checks that the file `package.conf` exists and does not contain any errors.
- Asks for missing or invalid parameters and creates `package.conf`.
- Executes make in the current directory to compile the application source code into an application binary file.
- Creates an EAP (Embedded Application Package) file with suffix `.eap` including the application binary, HTML files (if any) and configuration files.
- Creates a copy of `LICENSE` file.

The created application package filename has the following format:

```text
<PACKAGENAME>_<APPMAJORVERSION>_<APPMINORVERSION>_<APPMICROVERSION>_<SDK_ARCHITECTURE>.eap
```

The created copy of `LICENSE` filename has the following format:

```text
<PACKAGENAME>_<APPMAJORVERSION>_<APPMINORVERSION>_<APPMICROVERSION>_LICENSE.txt
```

## Build tool

For applications defined by `manifest.json`, use the build tool **acap-build**.

The acap-build tool does the following:

- Runs make, performing any required cross-compilation as defined in the available `Makefile`.
- Validates the manifest file against the manifest schema.
- Generates a `package.conf` file and related configuration files for backward compatibility.
- Creates an EAP file including:
  - application executable
  - `LICENSE` file
  - any available `html` and `lib` folder
  - other files listed in the acap-build request
  - generated backward compatibility files

For help on using the build tool, run `acap-build -h`.

> **Note**
>
> - If any additional files were previously listed in **OTHERFILES** in the `package.conf` file, these need to be listed as input to the acap-build command using the flag `-a`, for example `acap-build ./ -a file1 -a file2`.
> - At some point an EAP will be required to be based on a manifest file instead of a `package.conf` file. For such an ACAP application package to be supported in older firmware, a `package.conf` file is generated and included in the EAP file. Although it's the manifest file that is the base setup file for the ACAP application when building an EAP package in the SDK.
> - In the next step of introducing manifest file EAP files, systemd will start and stop the ACAP application. It then assumes execution failure if the main process dies, which means that the process must not fork off to a background process.

## Configure network proxy settings

With some network requirements, you must run the following script on the Axis device.

```sh
#!/bin/sh

# Setup proxy for dockerd

cat >> /etc/systemd/system/sdkrun_dockerd.service <<EOF
[Service]
Environment="HTTP_PROXY=http://<myproxy.com>:<port>"
Environment="HTTPS_PROXY=http://<myproxy>:<port>"
Environment="NO_PROXY=localhost,127.0.0.0/8,10.0.0.0/8,192.168.0.0/16,172.16.0.0/12,.<domain>"
EOF

systemctl daemon-reload
systemctl restart sdkrun_dockerd

exit
```

## Build, install and run with custom application image

For instructions on how to set up your build, to install, and to run with custom application image, use the **Hello World** application example shown in [Set up and verify the SDK](../get-started/set-up-and-verify-the-sdk).

Using the custom application image, all the building and packaging is done inside a Docker container. The application is then copied to a custom directory, meaning that the original application project directory is not changed.

The top structure for an ACAP application contains a Dockerfile and a directory called app where the application project files are placed.

To install, start, stop and remove the application, use the device's web interface.

## Build, install and run interactively inside container

To be able to work interactively with your application, you can bind mount the application project directory into the container. In this way, you can build and package the application directly in this folder. You may also install, start, stop and remove the application on a device directly from inside the container.

The top structure for an ACAP application contains a directory called, for example app where the application project files are placed.

To run the acap-sdk container interactively and mount the application project, go to the directory that contains app and run:

```sh
docker run -v $PWD/app:/opt/app -it hello_world:1.0
```

where:

- `axisecp/acap-sdk` is the Docker Hub repostitory
- `3.5-armv7hf-ubuntu20.04` is the tag that points out which SDK version and architecture to use
- `-v $PWD/app:/opt/app` mounts the host directory `$PWD/app` into the container directory `/opt/app`
- `--rm` removes the container after closing it
- `-i` is to run the container interactively
- `-t` which repository tag to use

You should end up in a container with a prompt similar to:

```sh
root@1e6b4f3d5a2c:/opt/app#
```

Now you're ready to build and install the application. See [Build the application](#build-the-application), and [Install the application](#install-the-application).

> **Note**
> The bind mount means that any changes made inside the container on `/opt/app` will be made to the host directory `$PWD/app`.

### Build the application

#### Using `package.conf` (ACAP SDK version 3.2 and earlier)

To build an application stand in the application directory inside the container
and run create-package.sh.

#### Using `manifest.json` (ACAP SDK version 3.3 and later)

To build an application, stand in the application directory inside the container
and run the acap-build tool.

### Install the application

The SDK helps with installing a built application on the device from a terminal. You can also install application packages, using the device's web interface. But this method is less convenient during application development.

To install a built application on a device, run:

```sh
eap-install.sh
```

Run the command without any options to get help.

To install a built application on a device, run the following command (you must enter the IP address and the root password of the device the first time):

```sh
eap-install.sh <device-ip> <password> install

eap-install.sh 192.168.0.90 pass install
```

The command remembers the device-ip and password after the first successful execution. After this you can simply run:

```sh
eap-install.sh install
```

> **Note**
> You must run the command from the application project directory, see [Application project structure](./application-project-structure.md).

### Start, stop and remove the application

Before you continue, make sure that you have done a first successful execution of shell script command `eap-install.sh`, see [Install the application](#install-the-application) for more information.

To start, stop and remove an installed application, run:

```sh
eap-install.sh [start|stop|remove]
```

To start an installed application on the device, run:

```sh
eap-install.sh start
```

Now you can see the status of the application using the device's web interface.

To stop a running application, run:

```sh
eap-install.sh stop
```

To remove an installed application, run:

```sh
eap-install.sh remove
```
