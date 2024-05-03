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
- [Check device properties](#check-device-properties) and update to the latest firmware (AXIS OS) if needed, see [How to upgrade](#how-to-upgrade)
- [Check device properties](#check-device-properties) and identify the device architecture to be able to choose the correct toolchain

## Find the device on the network

### Find the device

To find Axis devices on the network and assign them IP addresses in Windows®, use AXIS IP Utility or AXIS Device Manager. Both applications are free and can be downloaded from [axis.com/support](https://www.axis.com/support).

For more information about how to find and assign IP addresses, go to [How to assign an IP address and access your device](https://www.axis.com/products/online-manual/i90000).

### Access the device

1. Open a browser and enter the IP address or hostname of the Axis device.
2. Enter the username and password. If you access the device for the first time, you must set the root password. See [Set a new password for the root account](#set-a-new-password-for-the-root-account).
3. The live view page opens in your browser.

### Access the device through SSH

You can enable SSH on an Axis device either through the device's web interface or by calling a VAPIX API from command-line.

#### Through old web interface

1. Go to the following URL:
    - AXIS OS < 10.6 `http://192.168.0.90/#settings/system/tools/plainconfig`
    - AXIS OS >= 10.6 `http://192.168.0.90/aca/index.html#settings/system/tools/plainconfig`
2. Click on **Network** in the list
3. Under **SSH** select **Enabled**
4. Scroll to the bottom of the page and click button **Save**

#### Through new web interface

1. Go to `http://192.168.0.90/camera/index.html#/system/plainConfig`
2. Select the **Network** group from the drop-down menu
3. Under **Network / SSH** select **Enabled**
4. Scroll to the bottom of the page and click button **Save**

#### Through command-line

This is exemplified using `curl`:

```sh
curl -u '<username>:<password>' "http://192.168.0.90/axis-cgi/admin/param.cgi?action=update&Network.SSH.Enabled=yes"
```

> More options may be required depending on your network setup.

## Setup the device on the network

Some extra steps can be followed to make sure the device is ready to be used and connected to the network.

### Verify that no one has tampered with the firmware

To make sure that the device has its original firmware (AXIS OS), or to take full control of the device after a security attack:

1. Reset to factory default settings. See the product’s user manual for information on how to reset to factory default settings.
After the reset, secure boot guarantees the state of the device.
2. Configure and install the device.

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

To get basic device information, such as AXIS OS version and architecture, use VAPIX POST request and method **getAllProperties**:

```html
http://192.168.0.90/axis-cgi/basicdeviceinfo.cgi
```

To extract the messages, use the CGI from a terminal, using the credentials set in the network configuration:

```sh
curl --anyauth '*' -u '<username>:<password>' 192.168.0.90/axis-cgi/basicdeviceinfo.cgi --data '{"apiVersion":"1.0","context":"Client defined request ID","method":"getAllProperties"}'
```

The following response contains architecture `"Architecture": "armv7hf"`, and AXIS OS version `"Version": "9.50.1"`:

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

## How to upgrade

Axis offers product firmware (AXIS OS) management according to the active track or the long-term support (LTS) tracks. Regardless of the track chosen, it is recommended to upgrade AXIS OS regularly in order to get the latest security updates. AXIS OS can be upgraded using AXIS Device Manager, AXIS Camera Station, AXIS Companion, HTTP or FTP.

> If using AXIS A1001 in cluster mode, make sure to upgrade all controllers.
> Either all at a time using AXIS Device Manager or straight after each other
> using the web interface or FTP. The entire cluster should always be on the
> same firmware

### AXIS Device Manager or AXIS Camera Station

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

> By default, firmware upgrade is done for all the selected devices at the same
> time. The upgrade order can be changed in **Configuration > Connected
> services > Firmware upgrade settings**. Once a firmware update has been
> started, the devices will be unavailable until the installation and restart
> of the devices has completed successfully.

For more information, see the help in AXIS Device Manager/AXIS Camera Station.

### Device web interface

> The procedure to update firmware differs slightly depending on the version of
> the installed web interface (before and after 7.10.1). For AXIS Q1659, the
> new web interface was introduced in firmware version 6.55.1.

#### Upgrade instructions when using the old web interface

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

#### Upgrade instructions when using the new web interface

1. Download the upgrade file to a directory that is accessible from your local computer.
2. Open the product's start page (e.g. `http://192.168.0.90`) in a web browser.
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

### FTP

> - Starting with firmware version 7.30.1 and onwards, the FTP server is
>     disabled by default. In order to use the instructions below it first
>     needs to be enabled via the web interface: ***Settings > System >
>     PlainConfig > Network > NetworkFTP***
> - This section is not applicable for AXIS Companion Line cameras.

1. You must be at the command prompt and in the directory that contains the upgrade file. Example: `C:\Axis\Product\Firmware`
2. From the command prompt, open an FTP connection to the unit you wish to upgrade.
(Do not use a Windows based FTP program to do this, use command-line FTP programs only.)
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
