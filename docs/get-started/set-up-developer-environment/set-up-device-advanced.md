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
