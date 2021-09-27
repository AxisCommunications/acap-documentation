---
layout: page
parent: Service for partners
title: Package signing
nav_order: 2
---

## Package signing
The sign package service is available in the ACAP Service Portal, and requires ADP access.

By signing an ACAP package you make sure that the content of the package is not tampered with between the release and installation on the Axis device.

During the signing process, a signature is added at the end of the package. The signature is verified by the device when installing the ACAP.

Support for verifying signed ACAPs was introduced in firmware 9.20. The format as such is fully backward compatible. A signed ACAP can be installed on devices with a firmware earlier than 9.20, in which case it’s not verified by the device.


