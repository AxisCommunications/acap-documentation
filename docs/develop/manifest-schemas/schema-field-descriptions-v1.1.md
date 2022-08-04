---
layout: page
parent: Manifest schemas
title: Manifest schema v1.1
---

<h2 class='title-attention'><font color='red'>This document is automatically generated from manifest schema</font></h2>

# Field descriptions

All fields that are not marked as **Required** are optional

- **schemaVersion** `string` **Required**

  Specifies the application manifest schema version using two dot-separated integer numbers, which follow the semantic versioning rules for MAJOR and MINOR version numbers.

- **resources** `object`

  Host resources the application requires access to.

  - **dbus** `object`

    D-Bus resources on the host system that the application requires or desires access to.

  - **requiredMethods** `array`

      A list of D-Bus methods (given as strings) that are required by the application to be part of an API of the host system. If the methods are not present, the application is considered incompatible and will be rejected at installation.

  - **conditionalMethods** `array`

      A list of D-Bus methods (given as strings) desired by the application that may or may not be part of an API of the host system. If the methods are not present the application will still be installed. It is up to the application to handle the absence of the methods appropriately.

  - **linux** `object`

    Linux resources on the host system that the application requires or desires access to.

  - **user** `object`

      Dynamic user the application shall run as. The username of the dynamic user is determined at installation. If the application requires knowledge of the username it shall use the underlying OS functions to read it. Only one of dynamic user and static user (see acapPackageConf > setup > user) may be specified.

    - **groups** `array`

        A list of secondary groups (given as strings) the application user should belong to.

- **acapPackageConf** `object` **Required**

  An ACAP package configuration object.

  - **setup** `object` **Required**

    ACAP application identification and information settings.

  - **appName** `string` **Required**

      Name of the executable file.

  - **appId** `string`

      Application ID (provided by Axis). To retrieve an application ID, contact the Axis Technology Integration Partner Program support

  - **embeddedSdkVersion** `string`

      Minimum required SDK version that the device running the application must support. This field must be set to a version less than 3.0 if compatibility with pre-manifest firmware is needed. Otherwise the version should be set to 3.0

  - **friendlyName** `string`

      User friendly package name. The name that will be displayed e.g. in the embedded web pages.

  - **user** `object`

      Static user and group the application shall run as. Only one of dynamic user (see resources > linux > user) and static user may be specified.

    - **username** `string` **Required**

        Name of a user already existing on the device, used for application execution and file ownership.

    - **group** `string` **Required**

        Name of a user group already existing on the device, used for application execution.

  - **runMode** `string` **Required**

      If 'respawn' application will be restarted if exited. If 'never' application will never be restarted. If 'once' application will not be restarted if exited but will be restated on reboot of device if application is running.

  - **runOptions** `string`

      Optional application command line options

  - **vendor** `string` **Required**

      The company name of the provider and maintainer of the ACAP application.

  - **vendorUrl** `string`

      Link to the vendor home page.

  - **version** `string` **Required**

      The ACAP application version, following the semantic versioning rules.

  - **installation** `object`

    ACAP application installation settings

  - **postInstallScript** `string`

      Optional script that will be run on the Axis product after ACAP package installation completion. This must be a shell script located in the package root.

  - **configuration** `object`

    ACAP application interaction setup.

  - **settingPage** `string`

      The name of the main embedded web page of the ACAP application. To be refered to when listing installed ACAP applications. Must be located in directory 'html' relative to application package root.

  - **paramConfig** `array`

      A list of parameter configuration objects.

      A parameter object.

    - **name** `string` **Required**

        Name of the parameter.

    - **default** `string` **Required**

        Parameter default value.

    - **type** `string` **Required**

        Parameter type definition string.

  - **httpConfig** `array`

      A list of web server CGI configuration objects.

      A web server CGI configuration object.

    - **type** `string` **Required**

        CGI implementation type.

    - **name** `string` **Required**

        CGI path relative to application web root.

    - **access** `string` **Required**

        Access policy for calling the CGI.

  - **copyProtection** `object`

    ACAP application copy protection utilization

  - **method** `string` **Required**

      Copy protection mechanism.
