---
layout: page
grand_parent: Develop applications
parent: Manifest schemas
title: Manifest schema v1.3
---

<h2 class="title-attention"><font color='red'>This document is automatically generated from manifest schema</font></h2>

# Field descriptions

All fields that are not marked as **Required** are optional

- __schemaVersion__ `string` **Required**

    Specifies the application manifest schema version using two dot-separated integer numbers, which follow the semantic versioning rules for MAJOR and MINOR version numbers.

- __resources__ `object`

    Host resources the application requires access to.

    - __dbus__ `object`

        D-Bus resources on the host system that the application requires or desires access to.

        - __requiredMethods__ `array`

            A list of D-Bus methods (given as strings) that are required by the application to be part of an API of the host system. If the methods are not present, the application is considered incompatible and will be rejected at installation.

        - __conditionalMethods__ `array`

            A list of D-Bus methods (given as strings) desired by the application that may or may not be part of an API of the host system. If the methods are not present the application will still be installed. It is up to the application to handle the absence of the methods appropriately.

    - __linux__ `object`

        Linux resources on the host system that the application requires or desires access to.

        - __user__ `object`

            Dynamic user the application shall run as. The username of the dynamic user is determined at installation. If the application requires knowledge of the username it shall use the underlying OS functions to read it. Only one of dynamic user and static user (see acapPackageConf > setup > user) may be specified.

            - __groups__ `array`

                A list of secondary groups (given as strings) the application user should belong to.

- __acapPackageConf__ `object` **Required**

    An ACAP package configuration object.

    - __setup__ `object` **Required**

        ACAP application identification and information settings.

        - __appName__ `string` **Required**

            Name of the executable file.

        - __appId__ `string`

            Application ID (provided by Axis). To retrieve an application ID, contact the Axis Technology Integration Partner Program support

        - __architecture__ `string`

            The target architecture(s) that the ACAP application supports. Will be set at build time if missing.

        - __embeddedSdkVersion__ `string`

            Minimum required SDK version that the device running the application must support. This field must be set to a version less than 3.0 if compatibility with pre-manifest firmware is needed. Otherwise the version should be set to 3.0

        - __friendlyName__ `string`

            User friendly package name. The name that will be displayed e.g. in the embedded web pages.

        - __user__ `object`

            Static user and group the application shall run as. Only one of dynamic user (see resources > linux > user) and static user may be specified.

            - __username__ `string` **Required**

                Name of a user already existing on the device, used for application execution and file ownership.

            - __group__ `string` **Required**

                Name of a user group already existing on the device, used for application execution.

        - __runMode__ `string` **Required**

            If 'respawn' application will be restarted if exited. If 'never' application will never be restarted. If 'once' application will not be restarted if exited but will be restated on reboot of device if application is running.

        - __runOptions__ `string`

            Optional application command line options

        - __vendor__ `string` **Required**

            The company name of the provider and maintainer of the ACAP application.

        - __vendorUrl__ `string`

            Link to the vendor home page.

        - __version__ `string` **Required**

            The ACAP application version, following the semantic versioning rules.

    - __installation__ `object`

        ACAP application installation settings

        - __postInstallScript__ `string`

            Optional script that will be run on the Axis product after ACAP package installation completion. This must be a shell script located in the package root.

    - __uninstallation__ `object`

        ACAP application uninstallation settings

        - __preUninstallScript__ `string`

            Optional script that will be run on the Axis product before uninstallation of the ACAP. This must be a shell script located in the package root.

    - __configuration__ `object`

        ACAP application interaction setup.

        - __settingPage__ `string`

            The name of the main embedded web page of the ACAP application. To be refered to when listing installed ACAP applications. Must be located in directory 'html' relative to application package root.

        - __paramConfig__ `array`

            A list of parameter configuration objects.

            A parameter object.

            - __name__ `string` **Required**

                Name of the parameter.

            - __default__ `string` **Required**

                Parameter default value.

            - __type__ `string` **Required**

                Parameter type definition string.

        - __httpConfig__ `array`

            A list of web server CGI configuration objects.

            A web server CGI configuration object.

            - __type__ `string` **Required**

                CGI implementation type.

            - __name__ `string` **Required**

                CGI path relative to application web root.

            - __access__ `string` **Required**

                Access policy for calling the CGI.

    - __copyProtection__ `object`

        ACAP application copy protection utilization

        - __method__ `string` **Required**

            Copy protection mechanism.

