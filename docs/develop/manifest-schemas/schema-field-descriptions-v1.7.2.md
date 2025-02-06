---
layout: page
grand_parent: Develop ACAP applications
parent: Manifest schemas
title: Manifest schema v1.7.2
redirect_to: https://developer.axis.com/acap/develop/manifest-schemas/schema-field-descriptions-v1.7.2
---

<h2 class="title-attention"><font color="red">This document is automatically generated from manifest schema</font></h2>

# Field descriptions

All fields that are not marked as **Required** are optional

- **$schema** `string`

  URI of the manifest schema for validation

- **schemaVersion** `string` **Required**

  Specifies the application manifest schema version using three dot-separated integer numbers, which follow the semantic versioning rules for MAJOR, MINOR and PATCH version numbers.

- **resources** `object`

  Host resources the application requires access to.

  - **dbus** `object`

    D-Bus resources on the host system that the application requires or desires access to.

    - **requiredMethods** `array`

      A list of D-Bus methods (given as strings) that are required by the application to be part of an API of the host system. If the methods are not present, the application is considered incompatible and will be rejected at installation. A wildcard '*' can be supplied at the end of a string, preceeded by a dot '.', to match all methods of a D-Bus interface.

    - **conditionalMethods** `array`

      A list of D-Bus methods (given as strings) desired by the application that may or may not be part of an API of the host system. If the methods are not present the application will still be installed. It is up to the application to handle the absence of the methods appropriately. A wildcard '*' can be supplied at the end of a string, preceeded by a dot '.', to match all methods of a D-Bus interface.

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

    - **architecture** `string`

      The target architecture(s) that the ACAP application supports. Will be set at build time if missing.
      _Possible values:_ `all`, `aarch64`, `armv7hf`

    - **embeddedSdkVersion** `string`

      Minimum required SDK version that the device running the application must support. This field must be set to a version less than 3.0 if compatibility with pre-manifest firmware is needed. Otherwise the version should be set to 3.0

    - **friendlyName** `string`

      User-friendly package name. The name that will be displayed e.g. in the embedded web pages.

    - **user** `object`

      Static user and group the application shall run as. Only one of dynamic user (see resources > linux > user) and static user may be specified.

      - **username** `string` **Required**

        Name of a user already existing on the device, used for application execution and file ownership.

      - **group** `string` **Required**

        Name of a user group already existing on the device, used for application execution.

    - **runMode** `string` **Required**

      If 'respawn' application will be restarted if exited. If 'never' application will never be restarted. If 'once' application will not be restarted if exited but will be restarted on reboot of device if application is running.
      _Possible values:_ `respawn`, `once`, `never`

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

  - **uninstallation** `object`

    ACAP application uninstallation settings

    - **preUninstallScript** `string`

      Optional script that will be run on the Axis product before uninstallation of the ACAP. This must be a shell script located in the package root.

  - **configuration** `object`

    ACAP application interaction setup.

    - **settingPage** `string`

      The name of the main embedded web page of the ACAP application. To be refered to when listing installed ACAP applications. Must be located in directory 'html' relative to application package root.

    - **httpConfig** `array`

      A list of web server configuration objects.

      A web server CGI configuration object.

      - **type** `string` **Required**

        CGI implementation type.
        _Possible values:_ `transferCgi`, `fastCgi`

      - **name** `string` **Required**

        CGI path relative to application web root.

      - **access** `string` **Required**

        Access policy for calling the CGI.
        _Possible values:_ `admin`, `operator`, `viewer`

      A web content object.

      - **type** `string` **Required**

        Type of ACAP application web content. The type refers to the 'html' directory in the application package root.
        _Possible values:_ `directory`

      - **access** `string` **Required**

        Access policy for viewing ACAP application web content, i.e. all files that are stored under 'html' directory in the application package root. Default access policy is 'admin'. Be aware that changing access policies will give general access to the web content.
        _Possible values:_ `admin`, `operator`, `viewer`

    - **paramConfig** `array`

      A list of parameter configuration objects. It is possible to interact with these parameters using the Parameter API (axparameter), the [VAPIX API](https://www.axis.com/vapix-library/subjects/t10175981/section/t10036014/display) or from the settings web page of the ACAP application.

      A parameter object.

      - **name** `string` **Required**

        Name of the parameter.

      - **default** `string` **Required**

        Parameter default value.

      - **type** `string` **Required**

        Parameter type definition string.

    - **reverseProxy** `array`

      A list of reverse proxy configuration objects.

      A reverse proxy unix domain socket object.

      - **apiPath** `string` **Required**

        API path relative to the ACAP application home path.

      - **apiType** `string` **Required**

        API protocol (http, web socket or fast cgi).
        _Possible values:_ `http`, `ws`, `fcgi`

      - **target** `string` **Required**

        Target path to a unix domain socket.

      - **access** `string` **Required**

        Access policy for calling the path.
        _Possible values:_ `admin`, `operator`, `viewer`, `anonymous`

      A reverse proxy tcp object.

      - **apiPath** `string` **Required**

        API path relative to the ACAP application home path.

      - **target** `string` **Required**

        Target path. FastCGI or URI (http or web socket).

      - **access** `string` **Required**

        Access policy for calling the path.
        _Possible values:_ `admin`, `operator`, `viewer`, `anonymous`

    - **containers** `object`

      Container support required by or provided by the application.

      - **containerHost** `boolean`

        Application needs to be able to run containers. The host system will make preparations before the application starts, e.g. setting up subuid and subgid mappings and populate or clean up items in the /run filesystem.

      - **createDockerSymlinks** `boolean`

        Create symbolic links from various system-wide locations to Docker CLIs provided by this application.

  - **copyProtection** `object`

    ACAP application copy protection utilization

    - **method** `string` **Required**

      Copy protection mechanism.
      _Possible values:_ `none`, `axis`, `custom`

