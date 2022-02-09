---
layout: default
parent: Develop applications
title: Manifest schemas
has_children: true
nav_order: 2
---

# Manifest schemas
The pages listed in the Table of contents below contain manifest schema field
descriptions.

## Required fields
The structure of the fields can be seen by the list level. A Required field in
a sub-section means it's only required if the section above is chosen.

## Manifest schema version mapping
Mapping table for schema, firmware and SDK version.

> It's recommended to use the latest manifest version available for the minimum
> firmware version targeted.

| Schema | Firmware | SDK  | Description |
| :----- | :------- | :--  | :---------- |
| 1.0    | 10.7     | 1.0  | Initial basic version |
| 1.1    | 10.7     | 1.0  | Additional fields, mainly for technical reasons |
| 1.2    | 10.7     | 1.0  | Enables uninstall functionality which is required by e.g. docker-compose-acap |
| 1.3    | 10.9     | 1.1  | Architecture will be automatically generated and added to manifest at packaging step |
