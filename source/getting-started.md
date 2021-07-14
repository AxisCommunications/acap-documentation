---
layout: page
title: Getting started
---
## Pre-requisites
To develop ACAPs, you need the following:

- A computer with Linux, Windows, or MacOS.
- Docker. [Get Docker](https://docs.docker.com/get-docker/).
  - For Windows and MacOS, use the automatically upgradable **Docker desktop stable**.
  - For Linux, use **Docker community edition** version 18.09 or later.
- GIT scm. [GIT downloads](https://git-scm.com/downloads).
- We also recommend using Microsoft **Visual Studio Code**. But you are free to choose your favorite editor.

## Set up device
To prepare a device for development:

- [Find the device on the network](#find-the-device-on-the-network) to configure IP address and user credentials.
- [Check device compatibility](#check-device-compatibility) to make sure that you use a device that supports ACAP.
- [Check device properties](#check-device-properties) and update to the latest firmware if needed, see [How to upgrade](#how-to-upgrade).
- [Check device properties](#check-device-properties) and identify the device architecture to be able to choose the correct toolchain.

### Find the device on the network
To find Axis devices on the network and assign them IP addresses in Windows®, use AXIS IP Utility or AXIS Device Manager. Both applications are free and can be downloaded from [axis.com/support](https://www.axis.com/support).

For more information about how to find and assign IP addresses, go to [How to assign an IP address and access your device](https://www.axis.com/products/online-manual/i90000).

#### Access the device
1. Open a browser and enter the IP address or host name of the Axis device.
If you do not know the IP address, use AXIS IP Utility or AXIS Device Manager to find the device on the network.
2. Enter the username and password. If you access the device for the first time, you must set the root password. See [Set a new password for the root account](#set-a-new-password-for-the-root-account).
3. The live view page opens in your browser.

#### Verify that no one has tampered with the firmware
To make sure that the device has its original Axis firmware, or to take full control of the device after a security attack:
1. Reset to factory default settings. See the product’s user manual for information on how to reset to factory default settings.
After the reset, secure boot guarantees the state of the device.
2. Configure and install the device.

#### Secure passwords
> Axis devices send the initially set password in clear text over the network. To protect your device after the first login, set up a secure and encrypted HTTPS connection and then change the password.

The device password is the primary protection for your data and services. Axis devices do not impose a password policy as they may be used in various types of installations.

To protect your data we strongly recommend that you:

- Use a password with at least 8 characters, preferably created by a password generator.
- Don’t expose the password.
- Change the password at a recurring interval, at least once a year.

#### Set a new password for the root account
> The default administrator username is root. If the password for root is lost, reset the device to factory default settings. See [Reset to factory default settings](https://help.axis.com/#t10001042)

[![Password security confirmation check](https://www.axis.com/axistube/a5771bce93e200c36f7cd9dfd0e5deaa/38116/640/640.mp4_001.jpg)](https://youtu.be/yZkKTrGelao)

1. Type a password. Follow the instructions about secure passwords. See [Secure passwords](#secure-passwords).
2. Retype the password to confirm the spelling.
3. Click **Create login**. The password has now been configured.

### Check device compatibility
To check if device supports ACAP, use VAPIX CGI `http://192.168.0.90/axis-cgi/param.cgi` and check if the device supports EmbeddedDevelopment with a VAPIX GET/POST request and action list.

To extract the value of the parameter, use the CGI as device URL in a browser window:
```
http://192.168.0.90/axis-cgi/param.cgi?action=list&group=Properties.EmbeddedDevelopment.EmbeddedDevelopment
```

The following response shows a device that supports ACAP:
```
root.Properties.EmbeddedDevelopment.EmbeddedDevelopment=yes
```

### Check device properties
To get basic device information, such as firmware version and architecture, use VAPIX POST request and method **getAllProperties**:
```
http://192.168.0.90/axis-cgi/basicdeviceinfo.cgi
```
To extract the messages, use the CGI from a terminal, using the credentials set in the network configuration:
```
curl --anyauth "*" -u [username]:[password] 192.168.0.90/axis-cgi/basicdeviceinfo.cgi --data "{\"apiVersion\":\"1.0\",\"context\":\"Client defined request ID\",\"method\":\"getAllProperties\"}"
```

The following response contains architecture "Architecture": "armv7hf", and firmware version "Version": "9.50.1":
```
{
	"apiVersion": "1.0",
	"context": "Client defined request ID",
	"data": {
	"propertyList": {
		"Architecture": "armv7hf",
		"Brand": "AXIS",
		"BuildDate": "Nov 07 2019 11:16",
		"HardwareID": "764",
		"ProdFullName": "AXIS P1448-LE Network Camera",
		"ProdNbr": "P1448-LE",
		"ProdShortName": "AXIS P1448-LE",
		"ProdType": "Network Camera",
		"SerialNumber": "ACCC8ED0C9EC",
		"Soc": "Axis Artpec-6",
		"SocSerialNumber": "00000000-00000000-442C2402-87C00153",
		"Version": "9.50.1",
		"WebURL": "http://www.axis.com"
		}
	}
}
```

### How to upgrade
Axis offers product firmware management according to the active track or the long-term support (LTS) tracks. Regardless of the track chosen, it is recommended to upgrade the firmware regularly in order to get the latest security updates. The firmware can be upgraded using AXIS Device Manager, AXIS Camera Station, AXIS Companion, HTTP or FTP.

> If using AXIS A1001 in cluster mode, make sure to upgrade all controllers. Either all at a time using AXIS Device Manager or straight after each other using the web interface or FTP. The entire cluster should always be on the same firmware

#### AXIS Device Manager or AXIS Camera Station
1. Go to the **Device Manager Tab** in Axis Device Manager or **Configuration Tab > Devices - Management** in AXIS Camera Station.
2. Select all devices that should be upgraded.
3. Right click and select **Upgrade Firmware**, which will open a dialog with a list of device models and the current firmware version installed in each device.
4. In the **Upgrade Firmware** dialog there are two options:
    - **Check for Updates** which requires internet access.
    - **Browse** to locate firmware file e.g. on hard drive or memory stick.
5. Check for updates:
    - Select **Check for Updates** to download a list of all firmware available for all device models.
6. Browse:
    - Select **browse** to locate firmware files and import them. It is possible to select and import several files at the same time.
7. Each device model will show a dropdown containing all available firmware for a model. Firmware will be sorted by “Long Term Support” (LTS) and “Active” software tracks in the dropdown.
8. Select the firmware to install for each device model.
9. Click **OK** to start upgrading the devices.

> By default, firmware upgrade is done for all the selected devices at the same time. The upgrade order can be changed in **Configuration > Connected services > Firmware upgrade settings**. Once a firmware update has been started, the devices will be unavailable until the installation and restart of the devices has completed successfully.

For more information, see the help in AXIS Device Manager/AXIS Camera Station.

#### HTTP
> The procedure to update firmware differs slightly depending on the version of the installed web interface (before and after 7.10.1). For AXIS Q1659, the new web interface was introduced in firmware version 6.55.1.

**Upgrade instructions when using the old web interface**
1. Download the upgrade file to a directory that is accessible from your local computer.
2. Open the product's start page (e.g. `http://192.168.0.90`) in a web browser.
3. Click the **Setup** link and log in as "root" (or any other user with administrator privileges). You must be logged in as an administrator to upgrade the unit.
4. Click **System Options** in the menu to the left.
5. Click Maintenance.
6. Click the **Browse** button in the **Upgrade Server** section.
7. Select the upgrade file you downloaded (and maybe decompressed) from our site. This file is typically named after the product and firmware version.
8. Click the **Open** button.
9. Click the **Upgrade** button in the **Upgrade Server** section.
10. Wait for the flash load to complete, which may take 1-10 minutes. The upgrade procedure occurs in four steps:
    - Step 1: Shut down. Running applications are shut down and active connections are terminated.
    - Step 2: Uploading firmware. The old firmware will be erased and the new firmware will be saved. During this step, the power LED will blink green/amber. After a while the progress of the upgrade will be displayed in the web browser.
    - Step 3: Reboot. The system restarts automatically.
    - Step 4: Reconfiguration. The new firmware settings are configured to match the previous settings. The color of the status LED will be amber during this step.
11. After the upgrade has completed, the unit will automatically initiate the system, during which the status LED blinks amber. When initiation is complete and the system is ready for use, the status LED will be green.

**Upgrade instructions when using the new web interface**
1. Download the upgrade file to a directory that is accessible from your local computer.
2. Open the product's start page (e.g. http://192.168.0.90) in a web browser.
3. Log in as "root" (or any other user with administrator privileges).
4. Click **Settings** to the right.
5. Click **System-tab**.
6. Click **Maintenance**.
7. Select the upgrade file you downloaded (and maybe decompressed) from our site. This file is typically named after the product and firmware version.
8. Click the **Open** button.
9. Click the **Upgrade** button in the **Upgrade Server** section.
10. Wait for the flash load to complete, which may take 1-10 minutes. The upgrade procedure occurs in four steps:
    - Step 1: Shut down. Running applications are shut down and active connections are terminated.
    - Step 2: Uploading firmware. The old firmware will be erased and the new firmware will be saved. During this step, the power LED will blink green/amber. After a while the progress of the upgrade will be displayed in the web browser.
    - Step 3: Reboot. The system restarts automatically.
    - Step 4: Reconfiguration. The new firmware settings are configured to match the previous settings. The color of the status LED will be amber during this step.
11 . After the upgrade has completed, the unit will automatically initiate the system, during which the status LED blinks amber. When initiation is complete and the system is ready for use, the status LED will be green.

#### FTP
>   - Starting with firmware version 7.30.1 and onwards, the FTP server is disabled by default. In order to use the instructions below it first needs to be enabled via the web interface: ***Settings > System > PlainConfig > Network > NetworkFTP***
>   - This section is not applicable for AXIS Companion Line cameras.

1. You must be at the command prompt and in the directory that contains the upgrade file. Example: `C:\Axis\Product\Firmware`
2. From the command prompt, open an FTP connection to the unit you wish to upgrade.
(Do not use a Windows based FTP program to do this, use command line FTP programs only.)
3. Log in as “root”. You must be logged in as the root user to upgrade the unit.
4. Change to binary transfer mode by typing "bin" and press enter.
5. Type "hash" and press enter. This will allow you to see how the upgrade progresses.
6. Type the command "put XXX.bin flash" where XXX.bin is the name of the upgrade file you downloaded (and maybe decompressed) from our site. This file is typically named after the product and firmware version.
7. Wait for the flash load to complete, which may take 1-10 minutes. The upgrade procedure occurs in four steps:
    - Step 1: Shut down. Running applications are shut down and active connections are terminated.
    - Step 2: Uploading firmware. The old firmware will be erased and the new firmware will be saved. During this step, the power LED will blink green/amber. After a while, the progress of the upgrade will be displayed in the command prompt.
    - Step 3: Reboot. The FTP session terminates and the system starts automatically.
    - Step 4: Reconfiguration. The new firmware settings are configured to match the previous settings. The color of the status LED will be amber during this step.
8. After the upgrade has completed, the unit will automatically initiate the system, during which the status LED blinks amber. When initiation is complete and the system is ready for use, the color of the status LED will be green.

## Choose SDK
The ACAP SDK images are based on Ubuntu and contain the environment needed for building an AXIS Camera Application Platform (ACAP) application. All images are available on [Docker Hub](https://hub.docker.com/r/axisecp).

An SDK image can be used as a basis for custom built images to run your application, or as a developer environment inside the container. See examples in sections below for how to do this. 

Depending on your use case, use the [ACAP Native SDK](https://hub.docker.com/repository/docker/axisecp/acap-native-sdk), [ACAP Computer Vision SDK](https://hub.docker.com/r/axisecp/acap-computer-vision-sdk) or a combination of both. Remember to check [compatibility](devices) for your product before getting started.

## Hello world example

### ACAP Native SDK

#### Create a Hello World application

Create the following folder and file structure in a working directory:

```
hello-world
├── app
│   ├── hello_world.c
│   ├── LICENSE
│   ├── Makefile
│   └── manifest.json
├── Dockerfile
└── README.md
```

The files comprising the following:

**hello_world.c**

Hello World application which writes to system-log.

```
int main(int argc, char **argv)

{
  /* Open the syslog to report messages for "hello_world" */
  openlog("hello_world", LOG_PID | LOG_CONS, LOG_USER);

  /* Choose between { LOG_INFO, LOG_CRIT, LOG_WARN, LOG_ERR }*/
  syslog(LOG_INFO, "Hello World!");

  /* Close application logging to syslog */
  closelog();

  return 0;
}
```

**LICENSE**

Text file that lists all open source licensed source code distributed with the application.

**Makefile**

Makefile containing the build and link instructions for building the ACAP application.

> Make sure to preserve the tabs below. Recipes in a makefile must be preceded by a single standard tab character.

```
PROG1	= hello_world
OBJS1	= $(PROG1).c

PROGS	= $(PROG1)

CFLAGS-y  = -W -Wformat=2 -Wpointer-arith -Wbad-function-cast -Wstrict-prototypes -Wmissing-prototypes -Winline -Wdisabled-optimization -Wfloat-equal -Wall -Werror

all:	$(PROGS)

$(PROG1): $(OBJS1)
	$(CC) $^ $(CFLAGS) $(LIBS) -o $@
	$(STRIP) $@

clean:
	rm -f $(PROGS) *.o core *.eap
```

**manifest.json**

Defines the application and its configuration.

```
{
    "schemaVersion": "1.1",
    "acapPackageConf": {
        "setup": {
            "appName": "hello_world",
            "vendor": "Axis Communications",
            "embeddedSdkVersion": "3.0",
            "user": {
                "username": "sdk",
                "group": "sdk"
            },
            "runMode": "never",
            "version": "1.0.0"
        }
    }
}
```

**Dockerfile**

Docker file with the specified Axis toolchain and API container to build the example specified.

```
ARG ARCH=armv7hf
ARG VERSION=3.3
ARG UBUNTU_VERSION=20.04
ARG REPO=axisecp
ARG SDK=acap-sdk

FROM ${REPO}/${SDK}:${VERSION}-${ARCH}-ubuntu${UBUNTU_VERSION}


# Building the ACAP application
COPY ./app /opt/app/
WORKDIR /opt/app
RUN . /opt/axis/acapsdk/environment-setup* && acap-build ./
```

#### Build the Hello World application
Standing in your working directory run the following commands:

```
docker build --tag <APP_IMAGE> .
```

`<APP_IMAGE>` is the name to tag the image with, e.g., hello_world:1.0

Default architecture is **armv7hf**. To build for **aarch64** it's possible to update the `ARCH` variable in the Dockerfile or to set it in the docker build command via build argument:

```
docker build --build-arg ARCH=aarch64 --tag <APP_IMAGE> .
```

Copy the result from the build to a local directory build.

```
docker cp $(docker create <APP_IMAGE>):/opt/app ./build
```

The working directory now contains a build folder with the following files:

```
hello-world
├── app
│   ├── hello_world.c
│   ├── LICENSE
│   ├── Makefile
│   └── manifest.json
├── build
│   ├── hello_world*
│   ├── hello_world_1_0_0_armv7hf.eap
│   ├── hello_world_1_0_0_LICENSE.txt
│   ├── hello_world.c
│   ├── LICENSE
│   ├── Makefile
│   ├── manifest.json
│   ├── package.conf
│   ├── package.conf.orig
│   └── param.conf
├── Dockerfile
└── README.md
```

**build/hello_world*** – Application executable binary file.

**build/hello_world_1_0_0_armv7hf.eap** – Application package .eap file

**build/hello_world_1_0_0_LICENSE.txt** – Copy of LICENSE file.

**build/manifest.json** – Defines the application and its configuration.

**build/package.conf** – Defines the application and its configuration.

**build/package.conf.orig** – Defines the application and its configuration, original file.

**build/param.conf** – File containing application parameters.

#### Install and run the Hello World application

To install your application on an Axis video product:

1. Browse to the following page (replace `<axis_device_ip>` with the IP number of your Axis video product).
`http://<axis_device_ip>/#settings/apps`
2. Click Add, the + icon, and browse to the newly built `hello_world_1_0_0_armv7hf.eap`.
3. Click Install.

`hello_world` is now available as an application on the device.

To run the application:

1. Browse to the following page (replace `<axis_device_ip>` with the IP number of your Axis video product).
`http://<axis_device_ip>/#settings/apps`
2. Click the application icon.
3. **Start** the application.

**Expected output from the Hello World application**

You can find the application log at:

```
http://<axis_device_ip>/axis-cgi/admin/systemlog.cgi?appname=hello_world
```
or by clicking the App log link in the device GUI.

You can also extract the logs using the following commands in the terminal:

> Make sure SSH is enabled on the device to run the following commands.

```
tail -f /var/log/info.log | grep hello_world
```

**Output**

```
----- Contents of SYSTEM_LOG for 'hello_world' -----

14:13:07.412 [ INFO ] hello_world[6425]: Hello World!
```

#### Build and install the Hello World application inside container

Standing in your working directory, run the following command to bind mount the application directory in to the acap-sdk container:

```
docker run --rm -v $PWD/app:/opt/app -it hello_world:1.0 axisecp/acap-sdk:3.3-armv7hf-ubuntu20.04
```
Now inside the container, to build the application, run:

```
acap-build ./
```

The app directory now contains the following files:

```
├── Dockerfile
└── app
    ├── LICENSE
    ├── Makefile
    ├── hello_world*
    ├── hello_world.c
    ├── hello_world.o
    ├── hello_world_1_0_0_LICENSE.txt
    ├── hello_world_1_0_0_armv7hf.eap
    ├── manifest.json
    ├── package.conf
    ├── package.conf.orig
    └── param.conf
```
To install the application to a camera use command:

```
eap-install.sh --help
```


### ACAP Computer Vision SDK

#### Create a Hello World application
Create the following folder and file structure in a working directory:
```bash
opencv-hello-world-cpp
├── app
│   ├── Makefile
│   └── src
│       └── hello_world.cpp
├── docker-compose.yml
└── Dockerfile
```
The files contain the following:

**hello_world.c**

Hello World application which writes to standard out.
```cpp
#include <iostream>
#include <opencv2/core.hpp>

int main(void)
{
    std::cout << "Hello World from OpenCV " << CV_VERSION << "\n";
}
```
**Makefile**

Makefile containing the build and link instructions for building the ACAP application.
> Make sure to preserve the tabs below. Recipes in a makefile must be preceded by a single standard tab character.

```
TARGET = hello_world
OBJ = src/$(TARGET).o

CXX = arm-linux-gnueabihf-gcc
STRIP = arm-linux-gnueabihf-strip

CXXFLAGS += -I/usr/include -I/axis/opencv/usr/include
CPPFLAGS = -Os -pipe -std=c++17

BASE := $(abspath $(patsubst %/,%,$(dir $(firstword $(MAKEFILE_LIST)))))
LDLIBS += -L $(BASE)/lib \
 -L /usr/lib/gcc-cross/arm-linux-gnueabihf \
 -L /axis/opencv/usr/lib
LDLIBS += -lm -lstdc++ -lopencv_core

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $< $(CPPFLAGS) $(LDLIBS) -o $@ && $(STRIP) --strip-unneeded $@

clean:
	$(RM) *.o $(TARGET)
```
**Dockerfile**

Dockerfile based on the [ACAP Computer Vision SDK](https://hub.docker.com/r/axisecp/acap-computer-vision-sdk).
```
# Specify the architecture at build time: mipsis32r2el/armv7hf/aarch64
ARG ARCH=armv7hf
ARG REPO=axisecp
ARG SDK_VERSION=1.0-beta1
ARG RUNTIME_IMAGE=arm32v7/ubuntu:20.04

FROM ${REPO}/acap-computer-vision-sdk:${SDK_VERSION}-${ARCH}-runtime AS cv-sdk-runtime
FROM ${REPO}/acap-computer-vision-sdk:${SDK_VERSION}-${ARCH}-devel AS cv-sdk-devel

# Setup proxy configuration
ARG DOCKER_PROXY
ENV http_proxy=$DOCKER_PROXY
ENV https_proxy=$DOCKER_PROXY
ENV HTTP_PROXY=$DOCKER_PROXY
ENV HTTPS_PROXY=$DOCKER_PROXY

ENV DEBIAN_FRONTEND=noninteractive

## Install dependencies
RUN apt-get update && apt-get install -y -f \
    g++-arm-linux-gnueabihf \
    make\
    pkg-config \
    libglib2.0-dev \
    libsystemd0

RUN dpkg --add-architecture armhf &&\
    apt-get update && apt-get install -y  \
    libglib2.0-dev:armhf \
    libsystemd0:armhf

COPY app/Makefile /build/
COPY app/src/ /build/src/
WORKDIR /build
RUN make

FROM ${RUNTIME_IMAGE}
COPY --from=cv-sdk-devel /build/hello_world /usr/bin/
COPY --from=cv-sdk-runtime /axis/opencv /

CMD ["/usr/bin/hello_world"]
```

#### Build the Hello World application
```
docker build -t <APP_IMAGE> .
```
Default architecture is armv7hf. To build for aarch64 it's possible to update the ARCH variable in the Dockerfile or to set it in the docker build command via build argument. It might also be necessary to set a proxy for Docker to use, this is set using the HTTP_PROXY variable:
```
docker build -t <APP_IMAGE> --build-arg ARCH=aarch64 --build-arg DOCKER_PROXY=$HTTP_PROXY .
```

#### Install and run the Hello World application

> Installing and running the Hello World application requires the [Docker ACAP](https://hub.docker.com/r/axisecp/docker-acap) to be installed on the camera.

There are two options to run the capture app, either save the image locally as a .tar and upload it to the camera (*opt 1*),
or push the image to a container registry and pull the image to the camera from the cloud (*opt 2*).

**[opt 1] Save the image**

```
docker save -o opencv-app.tar <APP_IMAGE>
```
**[opt 1] Load the image**

```
docker -H tcp://$AXIS_TARGET_IP load -i opencv_app.tar
```
**[opt 2] push it to container registry.**

```
docker push <APP_IMAGE>
```
**[opt 2] pull it from a container registry:**

```
docker -H tcp://$AXIS_TARGET_IP <APP_IMAGE>
```
**Run the container**
```
docker-compose -H tcp://$AXIS_TARGET_IP:2375 -f docker-compose.yml up
```
**The expected output:**
```bash
Hello World from OpenCV <CV_VERSION>
```
