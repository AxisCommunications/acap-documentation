---
layout: page
grand_parent: Get started
parent: Set up developer environment
title: Set up device - advanced
nav_order: 3
---

# Set up device - advanced topics

- [Access the device through SSH](#access-the-device-through-ssh)

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
curl -u '<username>:<password>' --anyauth "http://192.168.0.90/axis-cgi/admin/param.cgi?action=update&Network.SSH.Enabled=yes"
```

### Create an SSH user

> - Prior to AXIS OS 11.5 it's only possible to SSH as `root` user.
> - From AXIS OS 11.5 it's possible to create a non-root SSH user.
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
> device, see [Create an SSH user](create-an-ssh-user).

```sh
ssh my-ssh-user@192.168.0.90
my-ssh-user@axis-aabbcc112233:~#
```
