---
layout: page
grand_parent: Get started
parent: Set up developer environment
title: Set up device - advanced
nav_order: 3
---

# Set up device - advanced topics

- [Access the device through SSH](#access-the-device-through-ssh)
- [Developer Mode](#developer-mode) get SSH user access for development purposes (AXIS OS 11.11 and later)

## Access the device through SSH

This section shows how to setup and log in to a device through Secure Shell
Protocol (SSH) to run command-line operations in AXIS OS.

### Enable SSH

SSH is by default disabled on Axis devices, but can be enabled either through
the device's web interface or by calling a VAPIX API from command-line.

#### Through new web interface

1. Go to `http://192.168.0.90/index.html#system/plainConfig`
2. Select the **Network** group from the drop-down menu
3. Under **Network / SSH** select **Enabled**
4. Scroll to the bottom of the page and click button **Save**

#### Through old web interface

1. Go to `http://192.168.0.90/index.html#settings/system/tools/plainconfig`
2. Click on **Network** in the list
3. Under **SSH** select **Enabled**
4. Scroll to the bottom of the page and click button **Save**

#### Through command-line

This is exemplified using `curl`:

> More options may be required depending on your network setup.

```sh
curl \
  -u <username>:<password> \
  --anyauth \
  "http://192.168.0.90/axis-cgi/admin/param.cgi?action=update&Network.SSH.Enabled=yes"
```

### Create an SSH user

> - Prior to AXIS OS 11.5 it's only possible to SSH as `root` user.
> - From AXIS OS 11.5 it's possible to create a non-root SSH user.
> - Starting from AXIS OS 11.11, an ACAP application user can get SSH access by enabling [Developer Mode](#developer-mode).
> - After AXIS OS 12.0 it will not be possible to SSH to an Axis device as
>   `root` user.

#### Through web interface

1. Go to the following URL:
    - AXIS OS < 11.6  `http://192.168.0.90/index.html#system/users`
    - AXIS OS >= 11.6 `http://192.168.0.90/index.html#system/accounts`
2. Find the field on the web page called:
    - AXIS OS < 11.6  **SSH users**
    - AXIS OS >= 11.6 **SSH accounts**
3. Click the `+` icon with text **Add SSH user**
4. Follow the instructions in the dialog to create an SSH user.

### Connect to the device

To connect to the Axis device through SSH, it's required to install a program
that can communicate via SSH. This will be exemplified using `ssh` and a
non-root SSH user called `my-ssh-user`.

> The SSH user needs to be created on the device before connecting to the
> device, see [Create an SSH user](#create-an-ssh-user).

```sh
ssh my-ssh-user@192.168.0.90
my-ssh-user@axis-aabbcc112233:~#
```

## Developer Mode

Developer Mode is a feature introduced in AXIS OS 11.11 that grants SSH access
to an ACAP application's dynamic user on an Axis device. When Developer Mode is
enabled, the ACAP application's dynamic user is added to the `ssh` group.

To enable Developer Mode on Axis devices running AXIS OS 11.11 or later, install
the `axis-unlock-acap-devmode` Custom Firmware Certificate (CFC) on the Axis device.

### Get the Custom Firmware Certificate (CFC)

To enable Developer Mode on your Axis devices, you need to obtain a unique CFC
for each individual unit. Axis partners are able to request a CFC through a web
service accessible at [CFC Portal](https://www.axis.com/support/cfcportal).

- If not already logged in to your MyAxis account you will be redirected to a
  log in page during the verification step.

To request a CFC, you will need to provide information about your device.
This information can be retrieved either by calling VAPIX APIs or by using the
device web interface, and is explained in the sections below.

Once you have gathered this information, you will be able to submit a request
for a CFC through the web service. If the request is successful, you will
receive a file ending with the suffix `.fcr`, which is the actual certificate
file you will need to install on your device.

#### Using VAPIX APIs

1. Use the [basicdeviceinfo API](https://developer.axis.com/vapix/network-video/basic-device-information#description) to retrieve:
   - **SerialNumber**: The serial number of the device.
    <!-- textlint-disable -->
   - **Soc**: The name of the device's SoC (system-on-chip), e.g., `artpec-7`, `artpec-8`, `ambarella-cv25`, etc.
    <!-- textlint-enable -->
   - **SocSerialNumber**: The unique identifier of the SoC, also referred to as **Processor Serial Number**.

2. Use the [OAK API](https://developer.axis.com/vapix/network-video/oak-api) to retrieve the Owner Authentication Key (OAK).

#### Using the device web interface

1. Navigate to the device's plain configuration page, typically at `http://192.168.0.90/index.html#system/plainConfig`.
    <!-- textlint-disable -->
2. Search for the **SerialNumber** and **Soc** values.
    <!-- textlint-enable -->
3. To get the OAK, navigate to the device's network configuration page, typically at `http://192.168.0.90/index.html#system/network`.
4. Scroll down to the **Owner authentication key (OAK)** section and press the **Get key** button.

### Install the CFC on your device

1. Navigate to the device's security configuration page, typically at `http://192.168.0.90/index.html#system/security`.
2. Scroll down to the **Custom Signed Firmware Certificate** section.
3. If `axis-unlock-acap-devmode` is not already installed, install it via the **Install** button.

### Verify Developer Mode is enabled

When Developer Mode is enabled on your device an SSH account will automatically
be created whenever an ACAP application is installed.

After installing an ACAP application, verify that a new SSH account is added by:

1. Navigate to the device's accounts configuration page, typically at `http://192.168.0.90/index.html#system/accounts`.
2. Scroll down to the **SSH accounts** section.
3. Verify that the **Enable SSH** switch is enabled.
4. Find the ACAP application user (named `acap-<appName>`).
5. To enable SSH access for the ACAP application user:
    - **Set a password for it** by pressing the three dots to the right and choosing **Update SSH account**. Setting the password is needed for SSH access.

> **Note** After updating your ACAP application, you might need to set the SSH password
> for the ACAP user again.
<!-- markdownlint-disable-line MD028 -->
> **Important** If the ACAP account is not present after installing your ACAP
> you might have to restart the device and then reinstall the ACAP application.
> Restarting the device can be done via the web interface in **Maintenance → Restart**.

### Disable Developer Mode

1. Navigate to the device's security configuration page, typically at `http://192.168.0.90/index.html#system/security`.
2. Scroll down to the **Custom Signed Firmware Certificate** section.
3. `axis-unlock-acap-devmode` will be listed as one of the **Installed certificates**. Press the three dots to the right of the certificate and choose **Delete certificate**.
4. Additionally, the device needs to be factory defaulted after removing the certificate for developer mode to be disabled.
   - Navigate to the device's maintenance page, typically at `http://192.168.0.90/index.html#maintenance`.
   - In the **Factory default** section press the `Default` button followed by `Restore all` in the popup frame.

To verify that developer mode is no longer active, one way is to install an ACAP
application and verify that no new ACAP SSH user is added.
