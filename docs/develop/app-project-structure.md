---
layout: page
parent: Develop applications
title: Application project structure
nav_order: 1
---

# Application project structure
An application project contains several files and directories for an application. The mandatory files are:

| File name 								 | Description|
| :------------------------- | :--------- |
| [application name].(c/cpp) | Source file/files in C/C++. |
| LICENSE 									 | Text file that lists all open source licensed source code distributed with the application. |
| Makefile 									 | Defines how the source code is compiled, includes dependencies and sets compilation error levels. |
| manifest.json 						 | Defines the application and its configuration.<br>Used at installation of the package.<br>See [Create a manifest file from scratch](#create-a-manifest-file-from-scratch) and [Create a manifest file from existing package.conf](#create-a-manifest-file-from-existing-packageconf) for more information. |

> * An eap package based on **manifest.json** is similar to one based on
> package.conf. The features previously configured using **package.conf** and
> special configuration files are now included in **manifest.json**.
> * Underneath, **package.conf** is generated from **manifest.json** and you
> might therefore see it during build time. Note however that the generated
> **package.conf** might be removed in the future.

Other optional files and directories to include:

| File Name 				 | Type         | Description |
| :----------------- | :----------- | :---------- |
| lib       				 | Directory    | Shared libraries custom to the application. |
| Postinstall Script | Shell Script | Executed at the installation of the application. |
| Preupgrade Script  | Shell Script | Executed before upgrading the application, available from firmware version 9.30. |

## Manifest file
The file **manifest.json** defines the application and its configuration.

An EAP package based on manifest.json is similar to one based on a package.conf.
The features previously configured using the package.conf and special
configuration files are now included in manifest.json.

For more information see:
* [Create a manifest file from scratch](#create-a-manifest-file-from-scratch)
* [Create a manifest file from existing package.conf](#create-a-manifest-file-from-existing-packageconf)
* [Manifest file content](#manifest-file-content)
* [Manifest file schema](#manifest-file-schema)
* [Discontinued support when using manifest file](#discontinued-support-when-using-manifest-file)

### Create a manifest file from scratch
Create a manifest.json file based on the manifest.json schema, see
[Manifest file schema](#manifest-file-schema).

To create the manifest file for a simple Hello Glib ACAP application:

**1. Create a minimal manifest.json file with basic metadata:**

* Friendly name
* Identifier and binary
* Vendor name
* Version

Example
```json
    "friendlyName": "Hello Glib",
    "appName": "hello_glib",
    "vendor": "Axis Communications",
    "version": "2.0.0"
```

**2. Define how you want the applications to be executed:**

* Running mode - the application keeps running at a reboot.
* User and group for execution and file ownership, typically the sdk:sdk.
* If needed, you could also define special start options for the execution of the binary.

Example
```json
    "runMode": "never",
    "user": {
      "group": "sdk",
      "username": "sdk"
    }
```

**3. Add the required embedded development version on the target device.**

Example
```json
    "embeddedSdkVersion": "3.0"
```

**4. Add any supported cgi endpoints.**

Example
```json
    "configuration": {
      "httpConfig": [
        {
          "access": "viewer",
          "name": "example.cgi",
          "type": "transferCgi"
        }
      ]
    }
```

The finished manifest.json
```json
{
  "schemaVersion": "1.2",
  "acapPackageConf": {
    "setup": {
      "friendlyName": "Hello Glib",
      "appName": "hello_glib",
      "vendor": "Axis Communications",
      "version": "2.0.0",
      "embeddedSdkVersion": "3.0",
      "runMode": "never",
      "user": {
        "group": "sdk",
        "username": "sdk"
      }
    },
    "configuration": {
      "httpConfig": [
        {
          "access": "viewer",
          "name": "example.cgi",
          "type": "transferCgi"
        }
      ]
    }
  }
}
```

### Create a manifest file from existing package.conf
If there is a package.conf file for the ACAP application project, you can use
it to generate an initial manifest.json file.

The easiest way to do this is to [run the SDK container interactively](build-install-run#build-install-and-run-interactively-inside-container). To generate
the initial manifest.json file, run `packageconf2manifest.py` inside your ACAP
project (that has an existing **package.conf** file). This generates a manifest
file based on that configuration. The manifest file should include everything
that is needed to build the EAP file.

For help on using **packageconf2manifest**, run `packageconf2manifest.py -h`.

### Manifest file content
The table below shows the package configuration with manifest file, in
relationship with the package.conf file.

For a list of all manifest fields and information on which that are required,
see [Manifest schemas](manifest-schemas).

| Setting |  With manifest file | In package conf and files | Description |
| :---    | :---                | :---                      | :---        |
| Application identifier and main binary | acapPackageConf.<br>setup.<br>appName | APPNAME | The name of the application’s executable binary file. |
| The user friendly name of the application | acapPackageConf.<br>setup.<br>friendlyName | PACKAGENAME<br>MENUNAME | A user-friendly package name, to be used by for instance device management software, when referring to the application. |
| Name of the application vendor | acapPackageConf.<br>setup.<br>vendor 	 |  VENDOR | The name of the vendor that created the application, to be used by for instance device management software, when referring to the vendor. |
| 															 | acapPackageConf.<br>setup.<br>vendorUrl | VENDORHOMEPAGELINK | Specifies a link to the vendor’s homepage, to be used by for instance device management software, when referring to the vendor. |
| Version for the ACAP application | acapPackageConf.<br>setup.<br>version | APPMAJORVERSION | A numerical value of the application’s major version. |
|                                  |                               | APPMINORVERSION | A numerical value of the application’s minor version. |
|                                  |                               | APPMICROVERSION | A numerical value of the application’s micro version. |
| User and group for execution and file ownership | acapPackageConf.<br>setup.<br>user.username | APPUSR | The user that the application will run as. The recommended user is **sdk**. |
|                                                 | acapPackageConf.<br>setup.<br>user.group 		|  APPGRP | The group that the application will run as. The recommended group is **sdk**. |
| Id of the application in Axis ACAP portal | acapPackageConf.<br>setup.<br>appId 	| APPID | The application copy protection identifier. Provided by Axis and required when using Axis copy protection solution. |
| The execution behavior of the application | acapPackageConf.<br>setup.<br>runMode | STARTMODE | Defines how the application is started. Possible values are:<br>- **respawn** Once started, the application starts automatically when the system starts (at boot). In case the application crashes, it restarts automatically.<br>- **once** Once started, the application starts automatically when the system starts (at boot). In case the application crashes, does not restart.<br>- **never** Application does not start or restart automatically. |
| Special options for binary execution 			| acapPackageConf.<br>setup.<br>runOptions | APPOPTS | Contains the application command line options (may be empty). |
| Open source licenses file | file: LICENSE | file: LICENSE | A file containing all open source licenses of the application. |
| Copy protection solution  | copyProtection.method | LICENSEPAGE | Specifies if a copy protection solution is used by the application. Possible values are:<br>- **axis** Protected by Axis copy protection license solution.<br>- **custom** Protected by a custom copy protection license solution, not provided by Axis.<br>- **none** Not protected by any license copy protection license solution. |
| Application specific installation script | acapPackageConf.<br>installation.<br>postInstallScript | POSTINSTALLSCRIPT | A script that runs on the device when the installation is completed. |
| Required embedded development version  	 | acapPackageConf.<br>setup.<br>embeddedSdkVersion[^1]   | REQEMBDEVVERSION | Specifies the minimum required embedded development version that the device running the application must support. The version is dependent on the set APIs used in the application. |
| Application specific setting page  			 | acapPackageConf.<br>configuration.<br>settingPage 			| SETTINGSPAGEFILE | 	Specifies the html page for custom settings, to be used by for instance device management software, allowing a user to browse the application settings page. The file must be in a directory called html in the application project. |
| Supported CGI endpoints | acapPackageConf.<br>configuration.<br>httpConfig[].name 	| HTTPCGIPATHS and file | CGI path relative to application web root |
| 												| acapPackageConf.<br>configuration.<br>httpConfig[].type 	| | CGI implementation type, e.g. transferCgi |
| 												| acapPackageConf.<br>configuration.<br>httpConfig[].access | | Access policy for calling the CGI  |
| Product integrated application parameters | acapPackageConf.<br>configuration.<br>paramConfig[].default | file: param.conf | Parameter default value |
| 																					| acapPackageConf.<br>configuration.<br>paramConfig[].name 		| | Name of the parameter |
| 																					| acapPackageConf.<br>configuration.<br>paramConfig[].type 		| | Parameter type definition string |
| Application specific web client pages | folder: html/ | folder: html/ |  |
| Application specific dynamically linked libraries | folder: lib/ |  folder: lib/ |  |

[^1]: `2.0` for manifest.json schema version 1.0 and earlier (for firmware
	version 10.5 and earlier). `3.0` for manifest.json schema version 1.1 and
	later. The minor version may need to be stepped up for certain APIs. See
	[API](../api/native-api) for more information.

### Manifest file schema
Manifest schemas have name format **application-manifest-schema-v\<X.Y\>.json**
and are found in the native SDK container under
**/opt/axis/acapsdk/axis-acap-manifest-tools/schema/schemas**.

You find descriptions of all available manifest fields for each version in
[Manifest schemas](manifest-schemas).


### Discontinued support when using manifest file
The following is no longer supported for an ACAP application, when using
manifest file:

* **Pre-upgrade script** – Script run before an ACAP application is installed as
an upgrade.
* **Forking main process** – Forking and demonizing of the ACAP application during
start.

> Instead of the application forking the main process, the application is
> started by systemd, which assumes failure if the main process dies, and writes
> any output to stdout/stderr to the system log.


## License file
The LICENSE file is included in the application package. It shall contain all
required open source license information for open source code distributed with
the application package.

> If LICENSE is empty the build fails.


## Local data
Application data such as configuration data and images should in runtime be
saved to the localdata directory of the application project's root directory.
The localdata directory is owned by APPUSR and the application has write access
to it, once installed on a device. All content in the localdata directory
remains after an application upgrade.

> _**Important!**_ Avoid continuous writes to **localdata** as it resides on a 
flash drive with limited write count per block. Internal wear leveling
minimizes the risk of failure, however, it is still strongly recommended to
avoid continuous writes.

> The available free space is product dependent.


