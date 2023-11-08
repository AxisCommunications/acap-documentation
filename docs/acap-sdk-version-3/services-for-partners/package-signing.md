---
layout: acap_sdk_version_3
parent: Services for partners
grand_parent: ACAP SDK version 3
title: Package signing
nav_order: 1
---
# Package signing

The sign package service is available in the ACAP Service Portal, and requires Technology Integration Partner Program access.

By signing an ACAP package you make sure that the content of the package is not tampered with between the release and installation on the Axis device.

During the signing process, a signature is added at the end of the application package. The signature is verified by the device when installing the ACAP application. Signing an application requires some fields to be set in the [manifest](../develop-applications/application-project-structure#manifest-file-content), for example, `vendor` and `architecture` (from [manifest schema 1.3](../../develop/manifest-schemas/) first released in ACAP SDK 3.5). You can find a full list of requirements
and other information in the Axis [ACAP Service Portal](../services-for-partners/acap-service-portal-for-administrators.md).

Support for verifying signed ACAP applications was introduced in firmware 9.20. The format as such is fully backward compatible. A signed ACAP application can be installed on devices with a firmware earlier than 9.20, in which case it's not verified by the
device.

A VAPIX API to toggle allowance of unsigned ACAP applications has been added in AXIS OS 11.2, see the API specifications in the [VAPIX documentation](https://www.axis.com/vapix-library/subjects/t10102231/section/t10036126/display?section=t10036126-t10185050).
