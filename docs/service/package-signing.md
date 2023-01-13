---
layout: page
parent: Service for partners
title: Package signing
nav_order: 2
---

## Package signing

The sign package service is available in the ACAP Service Portal, and requires Technology Integration Partner Program access.

By signing an ACAP package you make sure that the content of the package is not tampered with between the release and installation on the Axis device.

During the signing process, a signature is added at the end of the package. The signature is verified by the device when installing the ACAP.

Support for verifying signed ACAP applications was introduced in firmware 9.20. The format as such is fully backward compatible. A signed ACAP can be installed on devices with a firmware earlier than 9.20, in which case it’s not verified by the device.

A VAPIX API to toggle allowance of unsigned ACAP applications has been added in Axis OS 11.2, see the API specifications in the [VAPIX documentation](https://www.axis.com/vapix-library/subjects/t10102231/section/t10036126/display?section=t10036126-t10185050).
