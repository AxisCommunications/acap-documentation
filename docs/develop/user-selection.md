---
layout: page
parent: Develop ACAP applications
title: Migrating an application from static to dynamic user
nav_order: 10
redirect_to: https://developer.axis.com/acap/develop/user-selection
---

# Migrating an application from static to dynamic user

## Difference between the application user types

A native ACAP application runs on AXIS OS, and as with any application that runs on a Linux-based OS, it needs a valid user to run as. When creating the application the user can be selected in two ways. Either by selecting a **dynamic user**, i.e. a user that will be created for the application when it is installed, or by selecting a **static user**, i.e. a user that already exists on the device. **Dynamic user** is supported in all versions of ACAP Native SDK and is recommended to use. The dynamic user is also described in [User and group][user-group].

If setting up the ACAP application for a static user the `acapPackageConf.setup.user.username` and `acapPackageConf.setup.user.group` need to be specified in the manifest file. Naturally both the user and the group need to exist and need to be permitted to be selected. E.g. from AXIS OS 12.0 it will no longer be permitted to use the `root` user or group for an ACAP application.

### Example of manifest.json for an application with a static user

```json
{
    "schemaVersion": "1.7.0",
    "acapPackageConf": {
        "setup": {
            "appName": "static_user_app",
            "friendlyName": "App with static user",
            "vendor": "Axis Communications",
            "embeddedSdkVersion": "3.0",
            "runMode": "never",
            "version": "1.0.0",
            "user": {
                "group": "sdk",
                "username": "sdk"
            }
        }
    }
}
```

If setting up the ACAP application for a dynamic user neither `acapPackageConf.setup.user.username` nor `acapPackageConf.setup.user.group` shall be specified in the manifest file, as these will be set by the system. The name of the user will be `acap-<appName>` and the primary group `addon`. It is possible to specify one or more secondary groups that the user should belong to in the manifest. Again, any such group needs to exist and it needs to be permitted for the dynamic user to select that group. Also note that some **resources**, such as **dbus** in the manifest file are only supported for the dynamic user.

### Example of manifest.json for an application with a dynamic user

```json
{
    "schemaVersion": "1.7.0",
    "acapPackageConf": {
        "setup": {
            "appName": "dynamic_user_app",
            "friendlyName": "App with dynamic user",
            "vendor": "Axis Communications",
            "embeddedSdkVersion": "3.0",
            "runMode": "never",
            "version": "1.0.0"
        }
    }
}
```

### Static user vs. dynamic user

|                    | Static user                    | Dynamic user                   |
|--------------------|--------------------------------|--------------------------------|
| Availability       | Already existing on the device | Created when application is installed and removed when it is uninstalled |
| Primary group      | As set for the existing user   | `addon`                        |
| Secondary group(s) | As set for the existing user   | Set by `resources.linux.user.groups` in the manifest |
| Executing user     | Set by `acapPackageConf.setup.user.username` in the manifest | `acap-<appName>` where \<appName\> is set by `acapPackageConf.setup.appName` in the manifest |
| Executing group    | Set by `acapPackageConf.setup.user.group` in the manifest | `addon`                        |

## Handling permission issues when migrating from static to dynamic user

Since the basic case of a dynamic user only has the permissions given to it by being a member of the `addon` group it is easy to see that it would run in to permission issues for many use cases that a static user may be able to perform. Here we list different ways of solving these issues.

### Problem: Application user does not have group access to a required API

Some of the [supported APIs][apis] require that the application user is a member of the correct group in order to use them. One such example is the Edge Storage API, axstorage, that uses the `storage` group. This can be added to the dynamic user by setting `resources.linux.user.groups` to `["storage"]` as shown below. See the [axstorage example][axstorage_example] for a full description.

```json
{
    "schemaVersion": "1.7.0",
    "acapPackageConf": {
        "setup": {
            "appName": "dynamic_user_app",
            "friendlyName": "App with user in storage group",
            "vendor": "Axis Communications",
            "embeddedSdkVersion": "3.0",
            "runMode": "never",
            "version": "1.0.0"
        }
    },
    "resources": {
        "linux": {
            "user": {
                "groups": [
                    "storage"
                ]
            }
        }
    }
}
```

### Problem: Application can not GET or POST to VAPIX

From AXIS OS 11.6 it is possible to directly access VAPIX for a dynamic user application. In order to do this the application needs to request VAPIX access credentials via D-bus. The D-bus method to use must be specified in `resources.dbus.requiredMethods` in the manifest as shown below. See [VAPIX access for ACAP applications][vapix_access] for a full descriptionand the application [`vapix`][vapix_example] for an example.

```json
{
    "schemaVersion": "1.7.0",
    "acapPackageConf": {
        "setup": {
            "appName": "dynamic_user_app",
            "friendlyName": "App with VAPIX access",
            "vendor": "Axis Communications",
            "embeddedSdkVersion": "3.0",
            "runMode": "never",
            "version": "1.0.0"
        }
    },
    "resources": {
        "dbus": {
            "requiredMethods": [
                "com.axis.HTTPConf1.VAPIXServiceAccounts1.GetCredentials"
            ]
        }
    }
}
```

### Problem: Application can not serve a web page

Serving a web page can be done using a Reverse Proxy setup. This requires that `acapPackageConf.configuration.reverseProxy` is set in the manifest. One example of this is shown below. See [Web server via Reverse Proxy][reverse_proxy] for a full description. An example is available in [web-server][web_example].

```json
{
    "schemaVersion": "1.7.0",
    "acapPackageConf": {
        "setup": {
            "appName": "dynamic_user_app",
            "friendlyName": "App with reverse proxy",
            "vendor": "Axis Communications",
            "embeddedSdkVersion": "3.0",
            "runMode": "never",
            "version": "1.0.0"
        },
        "configuration": {
            "reverseProxy": [
                {
                    "apiPath": "my_web_server",
                    "target": "http://localhost:2001",
                    "access": "admin"
                }
            ]
        }
    }
}
```

## Migrating application with data stored on the device

When upgrading an application any files and folders stored in the application folder will be backed up and restored during the process. If the application user is changed between the initial version of the application and the upgrade version the ownership of the files and folders will be correctly set to the new user.
However, any files and folders stored, by the application, outside of the application folder, needs to be handled by the application itself.
If such data exists and the ownership of it needs to be migrated one work-around is to utilize either a post-install or a pre-uninstall script. Up until AXIS OS 11.11 LTS it is possible to run such scripts as the root user by setting the `AllowRoot` toggle to on. This is the case even when the application itself has a non-root user.
An example script for changing the ownership of files and folders:

```sh
#!/bin/sh -e

# Get the application user by asking for the owner of the applications localdata folder
UID_DOT_GID="$(stat -c %u.%g localdata)"

# Check if the script runs as root
IS_ROOT=$([ "$(id -u)" -eq 0 ] && echo true || echo false)

# Specify the path to data that needs ownership to be changed, e.g. on the SD card
APP_NAME="$(basename "$(pwd)")"
SD_CARD_AREA=/var/spool/storage/SD_DISK/areas/"$APP_NAME"

# Change ownership if the script runs as root and the data exists
if $IS_ROOT && [ -d "$SD_CARD_AREA" ]; then
 chown -R "$UID_DOT_GID" "$SD_CARD_AREA"
fi

```

<!-- Links to external references -->
<!-- markdownlint-disable MD034 -->
[apis]: ../api/native-sdk-api
[axstorage_example]: https://github.com/AxisCommunications/acap-native-sdk-examples/tree/main/axstorage
[reverse_proxy]: web-server-via-reverse-proxy
[user-group]: application-project-structure#user-and-group
[vapix_access]: VAPIX-access-for-ACAP-applications
[vapix_example]: https://github.com/AxisCommunications/acap-native-sdk-examples/tree/main/vapix
[web_example]: https://github.com/AxisCommunications/acap-native-sdk-examples/tree/main/web-server
<!-- markdownlint-enable MD034 -->
