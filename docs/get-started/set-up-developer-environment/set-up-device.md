---
layout: page
grand_parent: Get started
parent: Set up developer environment
title: Set up device
nav_order: 2
---

# Set up device

To prepare a device for development:

- [Find the device on the network](#find-the-device-on-the-network) to configure the IP address and the user credentials
- [Setup the device on the network](#setup-the-device-on-the-network) to make sure it's ready to be connected to the network
- [Check device compatibility](#check-device-compatibility) to make sure that you use a device that supports ACAP
- [Check device properties](#check-device-properties) and update to the latest AXIS OS version, see [How to upgrade](#how-to-upgrade)
- [Check device properties](#check-device-properties) and identify the device architecture to be able to choose the correct toolchain

> **AXIS OS** and **device software** were previously called **firmware**.

## Find the device on the network

### Find the device

To find Axis devices on the network and assign them IP addresses in Windows®, use AXIS IP Utility or AXIS Device Manager. Both applications are free and can be downloaded from [axis.com/support](https://www.axis.com/support).

For more information about how to find and assign IP addresses, go to [How to assign an IP address and access your device](https://www.axis.com/products/online-manual/i90000).

### Access the device

1. Open a browser and enter the IP address or hostname of the Axis device.
2. Enter the username and password. If you access the device for the first time, you must set the root password. See [Set a new password for the root account](#set-a-new-password-for-the-root-account).
3. The live view page opens in your browser.

## Setup the device on the network

Some extra steps can be followed to make sure the device is ready to be used and connected to the network.

### Verify that no one has tampered with the AXIS OS

To make sure that the device has its original AXIS OS, or to take full control of the device after a security attack:

1. Reset to factory default settings. See the product’s user manual for information on how to reset to factory default settings.
After the reset, secure boot guarantees the state of the device.
1. Configure and install the device.

### Set a secure password

> Axis devices send the initially set password in clear text over the network.
> To protect your device after the first login, set up a secure and encrypted
> HTTPS connection and then change the password.

The device password is the primary protection for your data and services. Axis devices do not impose a password policy as they may be used in various types of installations.

To protect your data we strongly recommend that you:

- Use a password with at least 8 characters, preferably created by a password generator.
- Don’t expose the password.
- Change the password at a recurring interval, at least once a year.

#### Set a new password for the root account

> The default administrator username is root. If the password for root is lost,
> reset the device to factory default settings. See the product’s user manual
> for information on how to reset to factory default settings.

[![Password security confirmation check](https://www.axis.com/axistube/a5771bce93e200c36f7cd9dfd0e5deaa/38116/640/640.mp4_001.jpg)](https://youtu.be/yZkKTrGelao)

1. Type a password. Follow the instructions about secure passwords, see [Set a secure password](#set-a-secure-password).
2. Retype the password to confirm the spelling.
3. Click **Create login**. The password has now been configured.

## Check device compatibility

To check if device supports ACAP, use VAPIX CGI `http://192.168.0.90/axis-cgi/param.cgi` and check if the device supports EmbeddedDevelopment with a VAPIX GET/POST request and action list.

To extract the value of the parameter, use the CGI as device URL in a browser window:

```html
http://192.168.0.90/axis-cgi/param.cgi?action=list&group=Properties.EmbeddedDevelopment.EmbeddedDevelopment
```

The following response shows a device that supports ACAP:

```bash
Properties.EmbeddedDevelopment.EmbeddedDevelopment=yes
```

## Check device properties

To get
[basic device information](https://www.axis.com/vapix-library/subjects/t10175981/section/t10132180/display),
such as AXIS OS version and architecture, use a VAPIX POST request and method **getAllProperties**:

```html
http://192.168.0.90/axis-cgi/basicdeviceinfo.cgi
```

To extract the messages, use the CGI from a terminal, using the credentials set in the network configuration:

```sh
curl \
  -u <username>:<password> \
  --anyauth \
  --data '{"apiVersion":"1.3","context":"Client defined request ID","method":"getAllProperties"}' \
  "http://192.168.0.90/axis-cgi/basicdeviceinfo.cgi"
```

> To get a pretty-print of the JSON response from the curl call, the program
> `jq` can be used by appending the following snippet `<curl command> | jq`

The following response contains architecture `"Architecture": "aarch64"`, and AXIS OS version `"Version": "12.0.91"`:

```json
{
  "apiVersion": "1.3",
  "data": {
    "propertyList": {
      "Architecture": "aarch64",
      "ProdNbr": "Q1656",
      "HardwareID": "900",
      "ProdFullName": "AXIS Q1656 Box Camera",
      "Version": "12.0.91",
      "ProdType": "Box Camera",
      "SocSerialNumber": "4E78C475-010102B7",
      "Soc": "Axis Artpec-8",
      "Brand": "AXIS",
      "WebURL": "http://www.axis.com",
      "ProdVariant": "",
      "SerialNumber": "B8A44F7D507D",
      "ProdShortName": "AXIS Q1656",
      "BuildDate": "Sep 26 2024 18:22"
    }
  },
  "context": "Client defined request ID"
}
```

## How to upgrade

Axis offers management of device software (AXIS OS) according to the active track or the long-term
support (LTS) tracks. Regardless of the track chosen, it is recommended to upgrade AXIS OS regularly
in order to get the latest security updates.

To manage AXIS OS upgrades in production sites it's recommended to use a
[Video Management Software](https://www.axis.com/products/video-management-software) (VMS) like the
AXIS Camera Station product family or a
[Device Management Software](https://www.axis.com/products/device-management-software). AXIS OS can
also be upgraded manually via web interface (see
[Upgrade via device web interface](#upgrade-via-device-web-interface)) or making a VAPIX call (see
[Upgrade with VAPIX](#upgrade-with-vapix)). Note that the new AXIS OS software file needs to be
available on the developer machine before making the upgrade, go to
[Download device software](https://www.axis.com/support/device-software).

### Upgrade via device web interface

> The procedure to update AXIS OS differs slightly depending on the version of the current device
> web interface.

#### Upgrade instructions for AXIS OS 10.0 and later

1. Open the product's start page (e.g. `http://192.168.0.90`) in a web browser.
2. Log in as user with administrator privileges.
3. Click **Maintenance** in the left menu.
4. In the **AXIS OS upgrade** (**Firmware upgrade** in AXIS OS 10) section, click the **Upgrade**
   button.
5. Click **Next**.
6. Select the AXIS OS software file you downloaded and click **Next**.
7. Select upgrade type and click **Next**.
8. Click **Upgrade**.
9. Wait for the flash load to complete, which may take 1-10 minutes. The upgrade procedure occurs
    in four steps:
    - Step 1: Shut down. Running applications are shut down and active connections are terminated.
    - Step 2: Uploading AXIS OS. The old AXIS OS will be erased and the new AXIS OS will be
      saved. During this step, the power LED will blink green/amber. After a while the progress of
      the upgrade will be displayed in the web browser.
    - Step 3: Reboot. The system restarts automatically.
    - Step 4: Reconfiguration. The new AXIS OS settings are configured to match the previous
      settings. The color of the status LED will be amber during this step.
10. After the upgrade has completed, the unit will automatically initiate the system, during which
    the status LED blinks amber. When initiation is complete and the system is ready for use, the
    status LED will be green.

#### Upgrade instructions for AXIS OS 7.10 to 9.80

1. Open the product's start page (e.g. `http://192.168.0.90`) in a web browser.
2. Log in as user with administrator privileges.
3. Click **Settings** to the right.
4. Click **System-tab**.
5. Click **Maintenance**.
6. Select the AXIS OS software file you downloaded.
7. Click the **Open** button.
8. Click the **Upgrade** button in the **Upgrade Server** section.
9. Wait for the flash load to complete, which may take 1-10 minutes. The upgrade procedure occurs in four steps:
    - Step 1: Shut down. Running applications are shut down and active connections are terminated.
    - Step 2: Uploading AXIS OS. The old AXIS OS will be erased and the new AXIS OS will be saved. During this step, the power LED will blink green/amber. After a while the progress of the upgrade will be displayed in the web browser.
    - Step 3: Reboot. The system restarts automatically.
    - Step 4: Reconfiguration. The new AXIS OS settings are configured to match the previous settings. The color of the status LED will be amber during this step.
10. After the upgrade has completed, the unit will automatically initiate the system, during which the status LED blinks amber. When initiation is complete and the system is ready for use, the status LED will be green.

#### Upgrade instructions for versions prior to AXIS OS 7.10

1. Open the product's start page (e.g. `http://192.168.0.90`) in a web browser.
2. Click the **Setup** link and log in as user with administrator privileges.
3. Click **System Options** in the menu to the left.
4. Click Maintenance.
5. Click the **Browse** button in the **Upgrade Server** section.
6. Select the AXIS OS software file you downloaded.
7. Click the **Open** button.
8. Click the **Upgrade** button in the **Upgrade Server** section.
9. Wait for the flash load to complete, which may take 1-10 minutes. The upgrade procedure occurs in four steps:
    - Step 1: Shut down. Running applications are shut down and active connections are terminated.
    - Step 2: Uploading AXIS OS. The old AXIS OS will be erased and the new AXIS OS will be saved. During this step, the power LED will blink green/amber. After a while the progress of the upgrade will be displayed in the web browser.
    - Step 3: Reboot. The system restarts automatically.
    - Step 4: Reconfiguration. The new AXIS OS settings are configured to match the previous settings. The color of the status LED will be amber during this step.
10. After the upgrade has completed, the unit will automatically initiate the system, during which the status LED blinks amber. When initiation is complete and the system is ready for use, the status LED will be green.

### Upgrade with VAPIX

To upgrade with the
[VAPIX Firmware management API](https://www.axis.com/vapix-library/subjects/t10175981/section/t10118139/display?section=t10118139-t10118145),
use a VAPIX POST request and method **upgrade**. To call this CGI from a terminal using the
credentials set in the network configuration and the downloaded AXIS OS software file:

```sh
curl \
  -u <username>:<password> \
  --anyauth \
  -F json='{"apiVersion": "1.5", "context": "Client defined request ID", "method": "upgrade"}' \
  -F file=@<PATH_TO_SOFTWARE_FILE> \
  "http://192.168.0.90/axis-cgi/firmwaremanagement.cgi"
```

The JSON response will look like this:

```json
{
  "apiVersion": "1.5",
  "method": "upgrade",
  "context": "Client defined request ID",
  "data": {
    "firmwareVersion": "12.0.91"
  }
}
```
