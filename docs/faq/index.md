---
layout: default
title: FAQ
nav_order: 10
---

<!-- omit from toc -->
# Frequently Asked Questions (FAQ)

- [Sign ACAP applications](#sign-acap-applications)
- [Deploy ACAP application](#deploy-acap-application)
- [What backbone/architecture do you recommend for TPU/ARTPEC-8/CV25?](#what-backbonearchitecture-do-you-recommend-for-tpuartpec-8cv25)
- [My model is developed for ARTPEC-7 (TPU). How do I run it on ARTPEC-8?](#my-model-is-developed-for-artpec-7-tpu-how-do-i-run-it-on-artpec-8)
- [What is the training process for the respective accelerator?](#what-is-the-training-process-for-the-respective-accelerator)
- [Cybersecurity and protecting models](#cybersecurity-and-protecting-models)

## Sign ACAP applications

Signing an ACAP application, and having the Axis device verify the signature on installation, is currently in development and has not been officially released.

In an upcoming [AXIS OS release](https://help.axis.com/axis-os), the Axis device will, using [VAPIX](https://www.axis.com/vapix-library/subjects/t10102231/section/t10036126/display?section=t10036126-t10185050), only accept signed ACAP applications, improving the device's security posture. As of AXIS OS 11.2, this is an opt-in feature, but at some point, the state of only accepting signed ACAP applications will be the default.

We recommend that you disable this check while developing your ACAP application. Once you are ready to use your application in production, you can sign it using the [ACAP Service Portal](../service-for-partners/acap-service-portal.md).

By signing your application, you add a level of protection during distribution. An installer or end-customer can trust that the application hasn't been tampered with, and they can also verify that it's your company that has built the application.

Members of the [Axis Technology Integration Partner (TIP)](https://www.axis.com/partner/technology-integration-partner-program) program automatically have access to the ACAP Service Portal. If you're not a partner, given you qualify for the program requirements, you can apply for access to the ACAP Service Portal. You need to have a registered company when applying.

## Deploy ACAP application

Given you only have one Axis device, deploying an ACAP application is pretty straightforward. You navigate to the device using a web browser and install and start the application in the Apps section utilizing the device's web pages. What about deploying the application to ten devices or even 1000? At some point, depending on your mileage, this becomes a significant problem. For information on how to deploy applications to a more substantial number of Axis devices, the following chapters guide you toward a few alternative options.

<!-- omit in toc -->
### Deploy ACAP application using AXIS Device Manager

[AXIS Device Manager](https://www.axis.com/support/tools/axis-device-manager) is a Windows application tailored toward device management in large installations. Follow these steps to deploy an ACAP application to many Axis devices:

1. In AXIS Device Manager select the devices.
2. Right-click any of the selected devices and select *Install Camera Application...* in the context menu.
3. Browse and select the ACAP application to install.
4. Select whether to install the licenses.
5. Click *Finish* to complete the wizard.
6. A task is created showcasing the progress and its outcome.

<!-- omit in toc -->
### Deploy ACAP application using PowerShell

The following alternative uses PowerShell to deploy an ACAP application to many Axis devices, each with its IP address, username, and password. PowerShell is available on Windows, macOS, and many Linux distributions. Make sure to use PowerShell 7 or higher. To determine the version of PowerShell you are using, run the `$PSVersionTable` command on a PowerShell prompt. See [Install PowerShell on Windows, Linux, and macOS](https://learn.microsoft.com/powershell/scripting/install/installing-powershell) on how to install or upgrade PowerShell on your computer.

First, create a file named `deploy.ps1` and add the following content:

```powershell
<#
  .PARAMETER Devices
  The filename containing the devices. The file should contain comma-separated
  values (CSV) where each line represents a device and contains the IP address,
  the username, and the password.
 
  Example:
 
  192.168.1.90,root,pass1
  192.168.1.91,root,pass2
 
  .PARAMETER App
  The filename of the ACAP application to be installed.
 
  .PARAMETER AppName
  The name of the ACAP application, as defined by its package configuration or
  manifest.
#>
param (
    [Parameter(Mandatory)] [string] $Devices,
    [Parameter(Mandatory)] [string] $App,
    [Parameter(Mandatory)] [string] $AppName
)
 
foreach ($device in Import-Csv -Path $Devices -Header "IP", "Username", "Password")
{
    $ip = $device.IP
    $username = $device.Username
    $password = $device.Password | ConvertTo-SecureString -AsPlainText -Force
    $credential = New-Object PSCredential -ArgumentList $username, $password
    $content = Get-Item $app
 
    Write-Host $ip
    Write-Host -NoNewline "  Install: "
    Write-Host -NoNewline $(Invoke-RestMethod -Credential $credential `
        -AllowUnencryptedAuthentication `
        -Method Post `
        -Uri "http://$ip/axis-cgi/applications/upload.cgi" `
        -ContentType "multipart/form-data" `
        -Form @{ file = $content })
    Write-Host -NoNewline "  Start:   "
    Write-Host -NoNewline $(Invoke-RestMethod -Credential $credential `
        -AllowUnencryptedAuthentication `
        -Method Post `
        -Uri "http://$ip/axis-cgi/applications/control.cgi?package=$AppName&action=start")
}
```

Now create a file named `devices.csv` describing the devices on which you want to deploy the ACAP application. The file should contain the device IP addresses, usernames, and passwords, formatted using comma-separated values (CSV). The following example file describes ten devices:

```text
192.168.1.90,root,pass1
192.168.1.91,root,pass2
192.168.1.92,root,pass3
192.168.1.93,root,pass4
192.168.1.94,root,pass5
192.168.1.95,root,pass6
192.168.1.96,root,pass7
192.168.1.97,root,pass8
192.168.1.98,root,pass9
192.168.1.99,root,pass10
```

The final piece to the puzzle is the actual ACAP application and its name, as defined by the package configuration or the manifest. Let's assume that the app is called `my_app.eap` and is located in the same directory as `deploy.ps1` and `devices.csv`. Regarding the application name, there is no good way to get hold of this other than to install the ACAP application on a device and view the URL of its logs. Please use the following steps to get the name of the ACAP application:

1. Install the ACAP application on an Axis device using its web pages.
2. When installed, view the logs either by selecting the *App log* link or the context menu (three vertical dots), depending on your version of the device interface.
3. Once the logs are shown, take note of the URL. In the URL <http://192.168.1.90/axis-cgi/admin/systemlog.cgi?appname=my_app>, the name of the application would be `my_app`.

With the ACAP application file and the application name, let's run the script that deploys the ACAP application on all devices.

```powershell
.\deploy.ps1 -Devices devices.csv -App my_app.eap -AppName my_app
```

Executing the command produces the following output describing a successful result.

```text
192.168.1.90
  Install: OK
  Start:   OK
192.168.1.91
  Install: OK
  Start:   OK
192.168.1.92
  Install: OK
  Start:   OK
192.168.1.93
  Install: OK
  Start:   OK
192.168.1.94
  Install: OK
  Start:   OK
192.168.1.95
  Install: OK
  Start:   OK
192.168.1.96
  Install: OK
  Start:   OK
192.168.1.97
  Install: OK
  Start:   OK
192.168.1.98
  Install: OK
  Start:   OK
192.168.1.99
  Install: OK
  Start:   OK
```

<!-- omit in toc -->
### Deploy ACAP application using Bash

The following alternative uses [Bash](https://en.wikipedia.org/wiki/Bash_(Unix_shell)) and [curl](https://curl.se/) to deploy an ACAP application to many Axis devices, each with their IP address, username, and password. Bash is available natively on Linux and macOS and can be accessed on Windows by [installing Windows Subsystem for Linux (WSL)](https://learn.microsoft.com/en-us/windows/wsl/install).

First, create a file named `deploy.sh` and add the following content:

```bash
#!/bin/bash
set -e
 
if [[ $# -ne 3 ]]; then
  echo "Error: Unsupported number of arguments"
  echo
  echo "USAGE:"
  echo "    install.sh <devices> <app> <app name>"
  echo
  echo "WHERE:"
  echo "    devices     The filename containing the devices. The file should contain comma-separated"
  echo "                values (CSV) where each line represents a device and contains the IP address,"
  echo "                the username, and the password."
  echo
  echo "                Example:"
  echo
  echo "                192.168.1.90,root,pass1"
  echo "                192.168.1.91,root,pass2"
  echo "    app         The filename of the ACAP application to be installed."
  echo "    app name    The name of the ACAP application, as defined by its package configuration or"
  echo "                manifest."
  exit 1
fi
 
devices=$1
app=$2
app_name=$3
 
while IFS="," read ip username password
do
  echo "$ip"
  echo -n "  Install: "
  curl --anyauth -u "$username:$password" -F packfil=@"$app" "http://$ip/axis-cgi/applications/upload.cgi"
  echo -n "  Start:   "
  curl --anyauth -u "$username:$password" "http://$ip/axis-cgi/applications/control.cgi?package=$app_name&action=start"
 
done < "$devices"
```

Mark the file as an executable:

```bash
chmod +x ./deploy.sh
```

Now create a file named `devices.csv` describing the devices on which you want to deploy the ACAP application. The file should contain the device IP addresses, usernames, and passwords, formatted using comma-separated values (CSV). The following file would describe ten devices:

```text
192.168.1.90,root,pass1
192.168.1.91,root,pass2
192.168.1.92,root,pass3
192.168.1.93,root,pass4
192.168.1.94,root,pass5
192.168.1.95,root,pass6
192.168.1.96,root,pass7
192.168.1.97,root,pass8
192.168.1.98,root,pass9
192.168.1.99,root,pass10
```

The final piece to the puzzle is the actual ACAP application and its name, as defined by the package configuration or the manifest. Let's assume that the app is called `my_app.eap` and is located in the same directory as `deploy.sh` and `devices.csv`. Regarding the application name, there is no good way to get hold of this other than to install the ACAP application on a device and view the URL of its logs. Please use the following steps to get the name of the ACAP application:

1. Install the ACAP application on an Axis device using its web pages.
2. When installed, view the logs either by selecting the *App log* link or the context menu (three vertical dots), depending on your version of the device interface.
3. Once the logs are shown, take note of the URL. In the URL <http://192.168.1.90/axis-cgi/admin/systemlog.cgi?appname=my_app>, the name of the application would be `my_app`.

With the ACAP application file and the application name, let's run the script that deploys the ACAP application on all devices.

```bash
./deploy.sh devices.csv my_app.eap my_app
```

Executing the command would produce the following output describing a successful result.

```text
192.168.1.90
  Install: OK
  Start:   OK
192.168.1.91
  Install: OK
  Start:   OK
192.168.1.92
  Install: OK
  Start:   OK
192.168.1.93
  Install: OK
  Start:   OK
192.168.1.94
  Install: OK
  Start:   OK
192.168.1.95
  Install: OK
  Start:   OK
192.168.1.96
  Install: OK
  Start:   OK
192.168.1.97
  Install: OK
  Start:   OK
192.168.1.98
  Install: OK
  Start:   OK
192.168.1.99
  Install: OK
  Start:   OK
```

<!-- omit in toc -->
### Deploy ACAP application using a programming language

There are only three things to consider when deploying an ACAP application using Python, NodeJS, or any other programming language:

- **Authentication** - Axis devices use [digest access authentication](https://en.wikipedia.org/wiki/Digest_access_authentication). All HTTP requests sent to the device must use this authentication protocol.
- **Uploading the ACAP application** - Use the `upload.cgi` to upload the application. The CGI is also used when updating an existing application, see the [VAPIX documentation](https://www.axis.com/vapix-library/subjects/t10102231/section/t10036126/display?section=t10036126-t10010609) for more information.
- **Starting the ACAP application** - Use the `control.cgi` to start the application. The CGI is also used when stopping the application, see the [VAPIX documentation](https://www.axis.com/vapix-library/subjects/t10102231/section/t10036126/display?section=t10036126-t10010606) for more information.

## What backbone/architecture do you recommend for TPU/ARTPEC-8/CV25?

The [FAQ in the ACAP Computer Vision example repository](https://github.com/AxisCommunications/acap-computer-vision-sdk-examples/discussions/112) explains a lot when it comes to model support for different Axis architectures.

## My model is developed for ARTPEC-7 (TPU). How do I run it on ARTPEC-8?

A few aspects of this question are answered in [ACAP Computer Vision SDK examples #112](https://github.com/AxisCommunications/acap-computer-vision-sdk-examples/discussions/112), but in general, a model that works on ARTPEC-7 can also work on ARTPEC-8. The difference is not about the model's architecture but an optimization stage called *quantization*. Make sure to use *quantization by tensor* on ARTPEC-8, since it is the most optimal solution on that platform.

[From Tensorflow model to larod inference on camera](https://github.com/AxisCommunications/acap-native-sdk-examples/tree/main/tensorflow-to-larod-artpec8) in the [ACAP Native SDK examples](https://github.com/AxisCommunications/acap-native-sdk-examples) repository also contains relevant information on model conversion, model quantization and image formats.

## What is the training process for the respective accelerator?

The [ACAP Native SDK examples](https://github.com/AxisCommunications/acap-native-sdk-examples) repository contains examples on the training process for [ARTPEC-7](https://github.com/AxisCommunications/acap-native-sdk-examples/tree/main/tensorflow-to-larod), [ARTPEC-8](https://github.com/AxisCommunications/acap-native-sdk-examples/tree/main/tensorflow-to-larod-artpec8) and [CV25](https://github.com/AxisCommunications/acap-native-sdk-examples/tree/main/tensorflow-to-larod-cv25).

## Cybersecurity and protecting models

How is my ACAP software and potential deep learning model (Intellectual Property) protected in the device?

An ACAP application is like any software that comes in a package. It can be inspected and reverse-engineered. We understand that anyone investing resources into software is concerned about someone copying it. It has been proven repeatedly that it's impossible to prevent someone from copying software available on the market. Even sophisticated copy protection mechanisms are commonly breached. However, it is hard to copy your know-how, support offering, partner network, etc. On top of this, legal action can be taken against trademark and patent infringements. Even if it's technically possible, it would, from a business perspective, not be possible.

When developing a deep learning model and AI applications, the most valuable assets are the knowledge about the end-customer and their problems. This know-how guides you through collecting the right training data, developing relevant system integrations, and building the business logic. This is an ongoing process where you add more and more value as your business and know-how grow.

Stealing parts of the solution from a device will not give anyone access to the training data to evolve the model. The same logic applies to Axis AI models and software that we have invested much in developing.

Axis provides a licensing mechanism that prevents ACAP applications from running without a valid license key. This gives you a mechanism to track how your ACAP is being used.
