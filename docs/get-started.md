---
layout: page
title: Get started
nav_order: 3
---

# Get started with ACAP application development

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
> The default administrator username is root. If the password for root is lost, reset the device to factory default settings. See [Reset to factory default settings](#set-a-new-password-for-the-root-account)

[![Password security confirmation check](https://www.axis.com/axistube/a5771bce93e200c36f7cd9dfd0e5deaa/38116/640/640.mp4_001.jpg)](https://youtu.be/yZkKTrGelao)

1. Type a password. Follow the instructions about secure passwords. See [Secure passwords](#secure-passwords).
2. Retype the password to confirm the spelling.
3. Click **Create login**. The password has now been configured.

### Check device compatibility
To check if device supports ACAP, use VAPIX CGI `http://192.168.0.90/axis-cgi/param.cgi` and check if the device supports EmbeddedDevelopment with a VAPIX GET/POST request and action list.

To extract the value of the parameter, use the CGI as device URL in a browser window:
```html
http://192.168.0.90/axis-cgi/param.cgi?action=list&group=Properties.EmbeddedDevelopment.EmbeddedDevelopment
```

The following response shows a device that supports ACAP:
```bash
root.Properties.EmbeddedDevelopment.EmbeddedDevelopment=yes
```

### Check device properties
To get basic device information, such as firmware version and architecture, use VAPIX POST request and method **getAllProperties**:
```html
http://192.168.0.90/axis-cgi/basicdeviceinfo.cgi
```
To extract the messages, use the CGI from a terminal, using the credentials set in the network configuration:
```bash
curl --anyauth "*" -u [username]:[password] 192.168.0.90/axis-cgi/basicdeviceinfo.cgi --data "{\"apiVersion\":\"1.0\",\"context\":\"Client defined request ID\",\"method\":\"getAllProperties\"}"
```

The following response contains architecture "Architecture": "armv7hf", and firmware version "Version": "9.50.1":
```json
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
The ACAP SDK images are based on Ubuntu and contain the environment needed for building an AXIS Camera Application Platform (ACAP) application. All images are available on [Docker Hub](https://hub.docker.com/u/axisecp).

An SDK image can be used as a basis for custom built images to run your application, or as a developer environment inside the container. See examples in sections below for how to do this.

Depending on your use case, use the [ACAP Native SDK](https://hub.docker.com/r/axisecp/acap-native-sdk), [ACAP Computer Vision SDK](https://hub.docker.com/r/axisecp/acap-computer-vision-sdk) or a combination of both. Remember to check [compatibility](axis-devices) for your product before getting started.

## Hello world example

### ACAP Native SDK
Create your first ACAP application from the [Hello World](https://github.com/AxisCommunications/acap-native-sdk-examples/tree/master/hello-world) example on Github which is a part of the [ACAP Native SDK examples](https://github.com/AxisCommunications/acap-native-sdk-examples).

### ACAP Computer Vision SDK

#### Create a Hello World application
This example demonstrates how to create a simple Python application using the ACAP Computer Vision SDK and run it on an edge device. This example's code is also available in the [Hello World](https://github.com/AxisCommunications/acap-computer-vision-sdk-examples/tree/master/hello-world-crosscompiled) example, which is a part of the [ACAP Computer Vision SDK examples](https://github.com/AxisCommunications/acap-computer-vision-sdk-examples).

Going from zero to a Python application running on an AXIS device is quite easy. First, the application script is written, as in the hello-world script. Next, the Dockerfile, which specifies the build of the the application image, is constructed. This needs to pull in packages from the ACAP Computer Vision SDK, as is done using the `COPY` commands. Finally, the application needs to be built and uploaded, as is specified below.

##### Requirements
To ensure compatibility with this example, the following requirements shall be met:
* Camera: ARTPEC-7 DLPU devices (e.g., Q1615 MkIII)
* docker-compose version 1.29 or higher
* Docker version 20.10.8 or higher
* Firmware: 10.7
* [docker-acap](https://hub.docker.com/u/axisecp/docker-acap) installed on the camera
* docker-acap set to use external memory card, see [documentation](https://github.com/AxisCommunications/docker-acap)

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
ARG SDK_VERSION=1.0-beta3
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
docker build -t $APP_NAME --build-arg REPO --build-arg ARCH --build-arg RUNTIME_IMAGE .
```

Next, the built image needs to be uploaded to the device. This can be done through a registry or directly. In this case, the direct transfer is used by piping the compressed application directly to the device's docker client:

```sh
docker save $APP_NAME | docker -H tcp://$AXIS_TARGET_IP load
```

With the application image on the device, it can be started. As this example does not use e.g., OpenCV, no special mounts are needed, making the run command very simple:

```sh
docker -H tcp://$AXIS_TARGET_IP run -it $APP_NAME
```

The expected output from the application is simply:

```sh
Hello World!
```
