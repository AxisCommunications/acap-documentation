---
layout: default
parent: Develop ACAP applications
title: Manifest schemas
has_children: true
nav_order: 2
redirect_to: https://developer.axis.com/acap/develop/manifest-schemas/
---

# Manifest schemas

The pages listed in the Table of contents below contain the generated manifest
schema field descriptions.

## Required fields

The structure of the fields can be seen by the list level. A required field in
a sub-section means it's only required if the section above is chosen.

## Manifest schema version mapping

Mapping table for manifest schema, AXIS OS and ACAP Native SDK version.

> It's recommended to use the latest manifest schema version available in the
> SDK. When [signing an ACAP
> application](../../service/acap-application-signing), the ACAP Portal will
> validate the manifest against the latest released manifest schema version
> within the same major version, which may contain bug fixes to the version
> included in the SDK.

> Note: To sign an ACAP application the minimum manifest schema version
> possible to use is 1.3 that introduced the for signing mandatory field
> `architecture`.

| Schema | AXIS OS | SDK  | Description |
| :----- | :------ | :--  | :---------- |
| 1.0    | 10.7    | 1.0  | Initial basic version. |
| 1.1    | 10.7    | 1.0  | Additional fields, mainly for technical reasons. |
| 1.2    | 10.7    | 1.0  | Enables uninstall functionality which is required by e.g. docker-compose-acap. |
| 1.3    | 10.9    | 1.1  | Add field `architecture`, which will be automatically generated and added to manifest at packaging step. |
| 1.3.1  | 11.0    | 1.4  | Bug fixes; Allow `=` in `runOptions` and `maxLength` of `appName` should be 26. |
| 1.4.0  | 11.7    | 1.11 | Allow new characters `( ) , . ! ? & '` for `vendor` field. |
| 1.5.0  | 11.8    | 1.12 | - Add support for reverse proxy configuration.<br> - Add access policy for ACAP application web content.<br> - Allow `-` character in secondary groups of `linux` resources.<br> - Allow strings in `requiredMethods` and `conditionalMethods` under `dbus` to end with `.*` to match all methods of a D-Bus interface. |
| 1.6.0  | 11.9    | 1.13 | - Add support for characters `$` and `\` in `apiPath` of the reverse proxy configuration.<br> - Add optional field `$schema` that can point out a manifest schema to use for manifest validation and auto-completion.<br> - Allow strings in `requiredMethods` and `conditionalMethods` under `dbus` to contain `-`. |
| 1.7.0  | 11.10    | 1.14 | Make preparations on the host system so the application can run containers, and create symbolic links from various system-wide locations to Docker CLIs provided by the application. |
| 1.7.1  | 12.0     | 12.0.0 | - Allow `user` and `group` names to contain hyphens `-`. <br> - Force `appName` to start with a regular letter and have length of at least 2. |
| 1.7.2  | 12.1     | 12.1.0 | Add restrictions to `friendlyName`:<br> - Disallow newline characters `\n` and `\r`.<br> - Set maximum length to 256 characters. |
| 1.7.3  | 12.2     | 12.2.0 | Allow reverse proxy `apiPath` of length 1. |
