---
layout: page
parent: Develop ACAP applications
title: Application project structure
nav_order: 1
---

<!-- omit in toc -->
# Application project structure

An application project contains several files and directories for an application. The mandatory files are:

| Filename          | Description|
| :------------------------- | :--------- |
| [application name].(c/cpp) | Source file/files in C/C++. |
| LICENSE           | Text file that lists all open source licensed source code distributed with the application. |
| Makefile           | Defines how the source code is compiled, includes dependencies and sets compilation error levels. |
| manifest.json        | Defines the application and its configuration.<br>Used at installation of the package.<br>See [Create a manifest file from scratch](#create-a-manifest-file-from-scratch) and [Create a manifest file from existing package.conf](#create-a-manifest-file-from-existing-packageconf) for more information. |

> - An eap package based on **manifest.json** is similar to one based on
> **package.conf**. The features previously configured using **package.conf** and
> special configuration files are now included in **manifest.json**.
> - Underneath, **package.conf** is generated from **manifest.json** and you
> might therefore see it during build time. Note however that the generated
> **package.conf** might be removed in the future. For now, it's generated for
> compatibility reasons.

Other optional files and directories to include:

| Filename      | Type         | Description |
| :----------------- | :----------- | :---------- |
| lib            | Directory    | Shared libraries custom to the application. |
| Postinstall Script | Shell Script | Executed at the installation of the application. |
| Preupgrade Script  | Shell Script | Executed before upgrading the application, available from AXIS OS version 9.30. |

<!-- omit in toc -->
## Manifest file

The file **manifest.json** defines the application and its configuration.

An EAP package based on manifest.json is similar to one based on a package.conf.
The features previously configured using the package.conf and special
configuration files are now included in manifest.json.

For more information see:

- [Create a manifest file from scratch](#create-a-manifest-file-from-scratch)
- [Create a manifest file from existing package.conf](#create-a-manifest-file-from-existing-packageconf)
- [Manifest file content](#manifest-file-content)
- [Manifest file schema](#manifest-file-schema)
- [Discontinued support when using manifest file](#discontinued-support-when-using-manifest-file)

### Create a manifest file from scratch

Create a manifest.json file based on the
[Manifest file schema](#manifest-file-schema).

To create the manifest file for a simple Hello World ACAP application:

**1. Create a minimal manifest.json file with schema version:**

- Schema version

Example

```json
{
    "schemaVersion": "1.5.0",
}
```

**2. Add basic metadata:**

- Friendly name
- Identifier and binary
- Vendor name
- Version

Example

```json
"acapPackageConf": {
    "setup": {
        "friendlyName": "Hello World",
        "appName": "hello_world",
        "vendor": "Axis Communications",
        "version": "1.0.0",
    }
}
```

**3. Add options for running mode:**

- Running mode - the option `never` means that the application will not start or restart automatically.
- embeddedSdkVersion  - the required embedded development version on the target device. Should always be set to `3.0` for new releases.

Example

```json
"acapPackageConf": {
    "setup": {
        "runMode": "never",
        "embeddedSdkVersion": "3.0",
    }
}
```

**4. The resulting file.**

The finished manifest.json, compare to the [Hello World](https://github.com/AxisCommunications/acap-native-sdk-examples/blob/master/hello-world/app/manifest.json) example manifest of the ACAP Native SDK examples.

```json
{
    "schemaVersion": "1.5.0",
    "acapPackageConf": {
        "setup": {
            "friendlyName": "Hello World",
            "appName": "hello_world",
            "vendor": "Axis Communications",
            "version": "1.0.0",
            "runMode": "never",
            "embeddedSdkVersion": "3.0",
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
see [Manifest schemas](manifest-schemas/).

| Setting |  With manifest file | In package conf and files | Description |
| :---    | :---                | :---                      | :---        |
| Application identifier and main binary | acapPackageConf.<br>setup.<br>appName | APPNAME | The name of the application’s executable binary file. |
| The user friendly name of the application | acapPackageConf.<br>setup.<br>friendlyName | PACKAGENAME<br>MENUNAME | A user-friendly package name, to be used by for instance device management software, when referring to the application. |
| Name of the application vendor | acapPackageConf.<br>setup.<br>vendor   |  VENDOR | The name of the vendor that created the application, to be used by for instance device management software, when referring to the vendor. Signing an application requires this field be set to the name you registered with as an [Axis Technology Integration Partner](https://www.axis.com/partner/technology-integration-partner-program) |
|                 | acapPackageConf.<br>setup.<br>vendorUrl | VENDORHOMEPAGELINK | Specifies a link to the vendor’s homepage, to be used by for instance device management software, when referring to the vendor. |
| Version for the ACAP application | acapPackageConf.<br>setup.<br>version | APPMAJORVERSION | A numerical value of the application’s major version. |
|                                  |                               | APPMINORVERSION | A numerical value of the application’s minor version. |
|                                  |                               | APPMICROVERSION | A numerical value of the application’s micro version. |
| User and group for execution and file ownership | acapPackageConf.<br>setup.<br>user.username | APPUSR | The user that the application will run as. It's recommended to use [dynamic user](#user-and-group) by not specifying user with this field.  |
|                                                 | acapPackageConf.<br>setup.<br>user.group   |  APPGRP | The group that the application will run as.  It's recommended to use [dynamic user](#user-and-group) by not specifying group with this field. |
| ID of the application in Axis ACAP portal | acapPackageConf.<br>setup.<br>appId  | APPID | The application copy protection identifier. Provided by Axis and required when using Axis copy protection solution. |
| Application architecture | acapPackageConf.<br>setup.<br>architecture[^1] | APPTYPE | The automatically generated architecture of the application. For architecture-independent applications, this field can be set to `all`. |
| The execution behavior of the application | acapPackageConf.<br>setup.<br>runMode | STARTMODE | Defines how the application is started. Possible values are:<br>- **respawn** Once started, the application starts automatically when the system starts (at boot). In case the application crashes, it restarts automatically.<br>- **once** Once started, the application starts automatically when the system starts (at boot). In case the application crashes, does not restart.<br>- **never** Application does not start or restart automatically. |
| Special options for binary execution    | acapPackageConf.<br>setup.<br>runOptions | APPOPTS | Contains the application command-line options (may be empty). |
| Open source licenses file | file: LICENSE | file: LICENSE | A file containing all open source licenses of the application. |
| Copy protection solution  | copyProtection.method | LICENSEPAGE | Specifies if a copy protection solution is used by the application. Possible values are:<br>- **axis** Protected by Axis copy protection license solution.<br>- **custom** Protected by a custom copy protection license solution, not provided by Axis.<br>- **none** Not protected by any license copy protection license solution. |
| Application specific installation script | acapPackageConf.<br>installation.<br>postInstallScript | POSTINSTALLSCRIPT | A shell script that runs on the device when the installation is completed. |
| Application specific uninstallation script | acapPackageConf.<br>uninstallation.<br>preUninstallScript | N/A | A shell script that runs on the device before uninstallation of application is started. |
| Required embedded development version    | acapPackageConf.<br>setup.<br>embeddedSdkVersion[^2]   | REQEMBDEVVERSION | Specifies the minimum required embedded development version that the device running the application must support. The version is dependent on the set APIs used in the application. |
| Application specific setting page      | acapPackageConf.<br>configuration.<br>settingPage    | SETTINGSPAGEFILE |  Specifies the HTML page for custom settings, to be used by for instance device management software, allowing a user to browse the application settings page. The file must be in a directory called `html` in the application project. |
| Supported CGI endpoints | acapPackageConf.<br>configuration.<br>httpConfig[].name  | HTTPCGIPATHS and file | CGI path relative to application web root |
|             | acapPackageConf.<br>configuration.<br>httpConfig[].type  | | CGI implementation type, e.g. transferCgi |
|             | acapPackageConf.<br>configuration.<br>httpConfig[].access | | Access policy for calling the CGI  |
| Product integrated application parameters | acapPackageConf.<br>configuration.<br>paramConfig[].default | file: param.conf | Parameter default value |
|                      | acapPackageConf.<br>configuration.<br>paramConfig[].name   | | Name of the parameter |
|                      | acapPackageConf.<br>configuration.<br>paramConfig[].type   | | Parameter type definition string |
| Application specific web client pages | folder: `html/` | folder: `html/` |  |
| Application specific dynamically linked libraries | folder: `lib/` |  folder: `lib/` |  |

[^1]: This parameter is generated at the build step for architecture-dependent applications and should not be added. For architecture-independent applications, e.g. like a [shell script](https://github.com/AxisCommunications/acap-native-sdk-examples/blob/master/shell-script-example/app/manifest.json), the architecture can be set to `all` in the manifest.json file.

[^2]: `2.0` for manifest.json schema version 1.0 and earlier (for AXIS OS version 10.5 and earlier). `3.0` for manifest.json schema version 1.1 and later. The minor version may need to be stepped up for certain APIs. See [API](../api/) for more information.

### Manifest file schema

Manifest schemas have name format **application-manifest-schema-v\<X.Y\>.json**
and are found in the native SDK container under
**/opt/axis/acapsdk/axis-acap-manifest-tools/schema/schemas**.

You find descriptions of all available manifest fields for each version in
[Manifest schemas](manifest-schemas).

### Discontinued support when using manifest file

The following is no longer supported for an ACAP application, when using
manifest file:

- **Pre-upgrade script** – Script run before an ACAP application is installed as
an upgrade.
- **Forking main process** – Forking and demonizing of the ACAP application during
start.

> Instead of the application forking the main process, the application is
> started by systemd, which assumes failure if the main process dies, and writes
> any output to stdout/stderr to the system log.

## User and group

- It's recommended to use **dynamic user** in ACAP applications.
- Up until ACAP version 3 SDK, it was recommended to set `sdk` as user and group.
- At some point in the future, the `sdk` user will be deprecated and removed.

### Dynamic user

To get a dynamic user, simply leave out `acapPackageConf.user.group` and `acapPackageConf.user.username`. The dynamic user will belong to the group `addon`.

An ACAP application with dynamic user will only have access to files installed under `/usr/local/packages/<appName>` and resources requested in the manifest.

The main advantage of using a dynamic user instead of `sdk` user is the higher level of security. The dynamic user does not have access to, and can not modify other ACAP applications.

### Secondary groups

If the user needs additional groups, this can be specified under `resources`.

Example

```json
    "resources": {
        "linux": {
            "user": {
                "groups": [
                    "storage"
                ]
            }
        }
    }
```

## License file

The LICENSE file is included in the application package. It shall contain all
required open source license information for open source code distributed with
the application package. Note

> If LICENSE is empty the build fails.

## Local data

Application data such as configuration data and images should in runtime be
saved to the localdata directory of the application project's root directory.
The localdata directory is owned by APPUSR and the application has write access
to it, once installed on a device. All content in the localdata directory
remains after an application upgrade.

> ***Important!*** Avoid continuous writes to **localdata** as it resides on a
flash drive with limited write count per block. Internal wear leveling
minimizes the risk of failure, however, it is still strongly recommended to
avoid continuous writes.

> The available free space is product dependent.
