---
layout: acap_sdk_version_3
parent: Get started
grand_parent: ACAP SDK version 3
title: Set up the device
nav_order: 4
redirect_to: https://developer.axis.com/acap/acap-sdk-version-3/get-started/set-up-the-device
---
# Set up the device

To prepare a device for development:

- [Find the device on the network](#find-the-device-on-the-network) to configure IP address and user credentials.
- [Setup the device on the network](#setup-the-device-on-the-network) to make sure it's ready to be connected to the network.
- [Check device compatibility](#check-device-compatibility) to make sure that you use a device that supports ACAP.
- [Check device properties](#check-device-properties) and update to the latest firmware if needed, see [How to upgrade](#how-to-upgrade).
- [Check device properties](#check-device-properties) and identify the device architecture to be able to choose the correct toolchain.

## Find the device on the network

To find Axis devices on the network and assign them IP addresses in Windows®, use AXIS IP Utility or AXIS Device Manager. Both applications are free and can be downloaded from [axis.com/support](https://www.axis.com/support).

For more information about how to find and assign IP addresses, go to [How to assign an IP address and access your device](https://help.axis.com/access-your-device).

### Access the device

1. Open a browser and enter the IP address or hostname of the Axis device. If you do not know the IP address, use AXIS IP Utility or AXIS Device Manager to find the device on the network.
2. Enter the username and password. If you access the device for the first time, you must set the root password. See [Set a new password for the root account](#set-a-new-password-for-the-root-account).
3. The live view page opens in your browser.

### Access the device with SSH

You can enable SSH on an Axis device either through the device's web interface or by calling a VAPIX API from command-line.

#### In the old web interface

1. Go to `http://192.168.0.90/index.html#settings/system/tools/plainconfig`
2. Click on **Network** in the list
3. Under **SSH** select **Enabled**
4. Scroll to the bottom of the page and click button **Save**

#### In the new web interface

1. Go to `http://192.168.0.90/index.html#system/plainConfig`.
2. Select the **Network** group from the drop-down menu.
3. Under **Network/SSH**, select **Enabled**.
4. Scroll to the bottom of the page and click **Save**.

#### Using command-line

In this example we're using curl, and more options may be required depending on your network setup:

```sh
curl --anyauth -u <username>:<password> "http://192.168.0.90/axis-cgi/admin/param.cgi?action=update&Network.SSH.Enabled=yes"
```

## Setup the device on the network

To make sure the device is ready to be used and connected to the network:

- Verify that no one has tampered with the firmware.
- Set a new password for the root account. See also Secure passwords.

### Verify that no one has tampered with the firmware

To make sure that the device has its original Axis firmware, or to take full control of the device after a security attack:

1. Reset to factory default settings. See the product's user manual for information on how to reset to factory default settings. After the reset, secure boot guarantees the state of the device.
2. Configure and install the device.

### Secure passwords

> Important
> Axis devices send the initially set password in clear text over the network. To protect your device after the first login, set up a secure and encrypted HTTPS connection and then change the password.

The device password is the primary protection for your data and services. Axis devices do not impose a password policy as they may be used in various types of installations.

To protect your data we strongly recommend that you:

- Use a password with at least 8 characters, preferably created by a password generator.
- Don't expose the password.
- Change the password at a recurring interval, at least once a year.

### Set a new password for the root account

> Important
> The default administrator username is root. If the password for root is lost, reset the device to factory default settings.

[![Support tip: Password security confirmation check](https://img.youtube.com/vi/yZkKTrGelao/maxresdefault.jpg)](https://youtu.be/yZkKTrGelao){:target="_blank"}

1. Type a password. Follow the instructions about secure passwords. See [Secure passwords](#secure-passwords).
2. Retype the password to confirm the spelling.
3. Click **Create login**. The password has now been configured.

## Check device compatibility

To check if device supports ACAP, use VAPIX CGI
`http://192.168.0.90/axis-cgi/param.cgi` and check if the device supports EmbeddedDevelopment with a VAPIX GET/POST request and action list.

To extract the value of the parameter, use the CGI as device URL in a browser window:

```text
http://192.168.0.90/axis-cgi/param.cgi?action=list&group=Properties.EmbeddedDevelopment.EmbeddedDevelopment
```

The following response shows a device that supports ACAP:

```text
root.Properties.EmbeddedDevelopment.EmbeddedDevelopment=yes
```

## Check device properties

To get basic device information, such as firmware version and architecture, use VAPIX POST request and method `getAllProperties`:

```text
http://192.168.0.90/axis-cgi/basicdeviceinfo.cgi
```

To extract the messages, use the CGI from a terminal, using the credentials set in the network configuration:

```sh
curl --anyauth -u <username>:<password> "http://192.168.0.90/axis-cgi/basicdeviceinfo.cgi" --data '{"apiVersion":"1.0","context":"Client defined request ID","method":"getAllProperties"}'
```

> To get a pretty-print of the JSON response from the curl call, the program
> `jq` can be used by appending the following snippet `<curl command> | jq`

The following response contains architecture `"Architecture": "armv7hf"`, and firmware version `"Version": "9.50.1"`:

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
            "WebURL": "<http://www.axis.com>"
        }
    }
}
```

## How to upgrade

Axis offers product AXIS OS management according to the active track or the long-term support (LTS) tracks. Regardless of the track chosen, it’s recommended to upgrade regularly in order to get the latest security updates. Upgrades can be done by using AXIS Device Manager, AXIS Camera Station, AXIS Companion or HTTP.

> Note
>
> - **AXIS A1001 in cluster mode**: If using AXIS A1001 in cluster mode, make sure to upgrade all controllers. Either all at a time using AXIS Device Manager or straight after each other using the web interface or FTP. The entire cluster should always be on the same version.
> - **Mandatory upgrade path (10.9)**: The following Axis devices require an upgrade via the latest available LTS 2018 (8.40) prior to upgrading to AXIS OS 10.9 or later: AXIS D2050-VE, AXIS FA54, AXIS M3057-PLVE, AXIS M3058-PLVE, AXIS P1367/-E, AXIS P1368-E, AXIS P1445-LE, AXIS P1445-LE-3, AXIS P1447-LE, AXIS P1448-LE, AXIS P3227-LV/-LVE, AXIS P3228-LV/-LVE, AXIS P3807-PVE, AXIS Q1645/-LE, AXIS Q1647/-LE, AXIS Q1659, AXIS Q3515-LV/-LVE, AXIS Q3517-LV/-LVE/-SLVE, D101-A XF P3807, ExCam XF P1367, ExCam XF Q1645 and F101-A XF P1367.
> - **Axis Edge Vault (10.11)**: From AXIS OS 10.11 and onwards, Axis Edge Vault will be upgraded automatically during an upgrade of the Axis device. The upgrade functionality introduces a non-backward compatible change to the behavior of Axis Edge Vault. The upgrade process is not reversible: once Axis Edge Vault has been upgraded, it cannot be downgraded. Installing an older release of AXIS OS on a device where Axis Edge Vault has been upgraded is highly discouraged. Core functionality such as HTTPS, 802.1x, and applications that are configured through the certificate management system will not work correctly. It is recommended to first upgrade through AXIS OS 10.10 and then to newer AXIS OS versions. This way, if the upgrade process fails or a rollback is triggered, the device will still be left with an AXIS OS system that is compatible with an upgraded Axis Edge Vault.

### AXIS Device Manager or AXIS Camera Station

1. Go to the **Device Manager Tab** in Axis Device Manager or **Configuration Tab** > **Devices - Management** in AXIS Camera Station.
2. Select all devices that should be upgraded.
3. Right click and select **Upgrade Firmware**, which will open a dialog with a list of device models and the current firmware version installed in each device.
4. In the **Upgrade Firmware** dialog there are two options:

    - **Check for Updates** which requires internet access.
    - **Browse** to locate the file e.g. on hard drive or memory stick.

5. Check for updates:

    - Select **Check for Updates** to download a list of all versions available for all device models.

6. Browse:

    - Select **Browse** to locate the files and import them. It is possible to select and import several files at the same time.

7. Each device model will show a dropdown containing all available versions for a model, sorted by "Long Term Support" (LTS) and "Active" software tracks.
8. Select the version to install for each device model.
9. Click **OK** to start upgrading the devices.

> **Note**
> By default, upgrade is done for all the selected devices at the same time. The upgrade order can be changed in **Configuration** > **Connected services** > **Firmware upgrade settings**. Once an update has been started, the devices will be unavailable until the installation and restart of the devices has completed successfully.

For more information, see the help in AXIS Device Manager/AXIS Camera Station.

### HTTP

> **Note**
> The procedure to update AXIS OS differs slightly depending on the version of the installed web interface (before and after 7.10.1). For AXIS Q1659, the new web interface was introduced in firmware version 6.55.1.

#### Upgrade instructions when using the old web interface

1. Download the upgrade file to a directory that is accessible from your local computer.
2. Open the product's start page (e.g. `http://192.168.0.90`) in a web browser.
3. Click the **Setup** link and log in as "root" (or any other user with administrator privileges). You must be logged in as an administrator to upgrade the unit.
4. Click **System Options** in the menu to the left.
5. Click **Maintenance**.
6. Click the **Browse** button in the **Upgrade Server** section.
7. Select the upgrade file you downloaded (and maybe decompressed) from our site. This file is typically named after the product and AXIS OS version.
8. Click the **Open** button.
9. Click the **Upgrade** button in the **Upgrade Server** section.
10. Wait for the flash load to complete, which may take 1-10 minutes. The upgrade procedure occurs in four steps:

    1. Shut down - Running applications are shut down and active connections are terminated.
    2. Uploading - The old version will be erased and the new will be saved. During this step, the power LED will blink green/amber. After a while the progress of the upgrade will be displayed in the web browser.
    3. Reboot - The system restarts automatically.
    4. Reconfiguration - The new versions settings are configured to match the previous settings. The color of the status LED will be amber during this step.

11. After the upgrade has completed, the unit will automatically initiate the system, during which the status LED blinks amber. When initiation is complete and the system is ready for use, the status LED will be green.

#### Upgrade instructions when using the new web interface

1. Download the upgrade file to a directory that is accessible from your local computer.
2. Open the product's start page (e.g. `http://192.168.0.90`) in a web browser.
3. Log in as "root" (or any other user with administrator privileges).
4. Click **Settings** to the right.
5. Click **System-tab**.
6. Click **Maintenance**.
7. Select the upgrade file you downloaded (and maybe decompressed) from our site. This file is typically named after the product and AXIS OS version.
8. Click the **Open** button.
9. Click the **Upgrade** button in the **Upgrade Server** section.
10. Wait for the flash load to complete, which may take 1-10 minutes. The upgrade procedure occurs in four steps:

    1. Shut down - Running applications are shut down and active connections are terminated.
    2. Uploading - The old version will be erased and the new will be saved. During this step, the power LED will blink green/amber. After a while the progress of the upgrade will be displayed in the web browser.
    3. Reboot - The system restarts automatically.
    4. Reconfiguration - The new versions settings are configured to match the previous settings. The color of the status LED will be amber during this step.

11. After the upgrade has completed, the unit will automatically initiate the system, during which the status LED blinks amber. When initiation is complete and the system is ready for use, the status LED will be green.

### FTP

> **Note**
>
> - Only applicable for AXIS OS versions 11.0 and below. With AXIS OS 11.1 and later, the FTP options has been removed to increase overall minimum cybersecurity level.
> - With AXIS OS 7.30.1 - 11.0, the FTP server is disabled by default. In order to use the instructions below it first needs to be enabled via the web interface: **Settings** > **System** > **Plain config** > **Network** > **NetworkFTP**
> - This section is not applicable for AXIS Companion Line cameras.

1. You must be at the command prompt and in the directory that contains the upgrade file. Example: `C:\Axis\Product\Firmware`
2. From the command prompt, open an FTP connection to the unit you wish to upgrade. (Do not use a Windows based FTP program to do this, use command-line FTP programs only.)
3. Log in as "root". You must be logged in as the root user to upgrade the unit.
4. Change to binary transfer mode by typing "bin" and press enter.
5. Type "hash" and press enter. This will allow you to see how the upgrade progresses.
6. Type the command "put XXX.bin flash" where XXX.bin is the name of the upgrade file you downloaded (and maybe decompressed) from our site. This file is typically named after the product and AXIS OS version.
7. Wait for the flash load to complete, which may take 1-10 minutes. The upgrade procedure occurs in four steps:
   1. Shut down - Running applications are shut down and active connections are terminated.
   2. Uploading - The old version will be erased and the new will be saved. During this step, the power LED will blink green/amber. After a while, the progress of the upgrade will be displayed in the command prompt.
   3. Reboot - The FTP session terminates and the system starts automatically.
   4. Reconfiguration - The new versions settings are configured to match the previous settings. The color of the status LED will be amber during this step.
8. After the upgrade has completed, the unit will automatically initiate the system, during which the status LED blinks amber. When initiation is complete and the system is ready for use, the color of the status LED will be green.
