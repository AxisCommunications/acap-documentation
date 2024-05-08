---
layout: default
parent: Develop ACAP applications
title: Manifest schemas
has_children: true
nav_order: 2
---

# Manifest schemas

The pages listed in the Table of contents below contain the generated manifest
schema field descriptions.

## Required fields

The structure of the fields can be seen by the list level. A required field in
a sub-section means it's only required if the section above is chosen.

## Manifest schema version mapping

Mapping table for manifest schema, AXIS OS and ACAP Native SDK version.

> It's recommended to use the latest manifest version available for the minimum
> AXIS OS version targeted.

| Schema | AXIS OS | SDK  | Description |
| :----- | :------ | :--  | :---------- |
| 1.0    | 10.7    | 1.0  | Initial basic version |
| 1.1    | 10.7    | 1.0  | Additional fields, mainly for technical reasons |
| 1.2    | 10.7    | 1.0  | Enables uninstall functionality which is required by e.g. docker-compose-acap |
| 1.3    | 10.9    | 1.1  | Architecture will be automatically generated and added to manifest at packaging step |
| 1.3.1  | 11.0    | 1.4  | Bug fixes; Allow `=` in `runOptions` and `maxLength` of `appName` should be 26 |
| 1.4.0  | 11.7    | 1.11 | Allow new characters `( ) , . ! ? & '` for `vendor` field |
| 1.5.0  | 11.8    | 1.12 | - Add support for reverse proxy configuration.<br> - Add access policy for ACAP application web content.<br> - Allow `-` character in secondary groups of `linux` resources.<br> - Allow strings in `requiredMethods` and `conditionalMethods` under `dbus` to end with `.*` to match all methods of a D-Bus interface. |
| 1.6.0  | 11.9    | 1.13 | - Add support for characters `$` and `\` in `apiPath` of the reverse proxy configuration.<br> - Add optional field `$schema` that can point out a manifest schema to use for manifest validation and auto-completion.<br> - Allow strings in `requiredMethods` and `conditionalMethods` under `dbus` to contain `-`. |
