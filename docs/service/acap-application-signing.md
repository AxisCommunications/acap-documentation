---
layout: page
parent: Service for partners
title: ACAP application signing
nav_order: 2
---

## ACAP application signing

The sign package service is available in the ACAP Service Portal, and requires Technology Integration Partner Program access.

By signing an ACAP package you make sure that the content of the package is not tampered with between the release and installation on the Axis device.

During the signing process, a signature is added at the end of the application package. The signature is verified by the device when installing the ACAP application. Signing an application requires some fields to be set in the [manifest](../develop/application-project-structure#manifest-file-content), e.g. **vendor** and **architecture** (from [manifest schema 1.3](../develop/manifest-schemas) first released in ACAP Native SDK 1.1). A full list of requirements and other information can be found in the Axis [ACAP Service Portal](acap-service-portal).

Support for verifying signed ACAP applications was introduced in firmware 9.20. The format as such is fully backward compatible. A signed ACAP application can be installed on devices with a firmware earlier than 9.20, in which case it’s not verified by the device.

A VAPIX API to toggle allowance of unsigned ACAP applications has been added in AXIS OS 11.2, see the API specifications in the [VAPIX documentation](https://www.axis.com/vapix-library/subjects/t10102231/section/t10036126/display?section=t10036126-t10185050).
