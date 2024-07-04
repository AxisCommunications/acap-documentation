---
layout: page
parent: Service for partners
title: ACAP application signing
nav_order: 2
---

## ACAP application signing

ACAP application signing is the process of adding a digital signature to your ACAP application to ensure that it hasn't been tampered with and that it has been built by your company. This provides an additional layer of security and trustworthiness for your application.

### Why sign your application?

By signing your ACAP application, you can:

- Ensure that the application hasn't been tampered with during distribution.
- Verify that the application was built by your company.
- Increase the security and trustworthiness of your application.

### How to sign your application

To sign your ACAP application, you'll need access to the [ACAP Service Portal](acap-service-portal), which is currently restricted to members of the [Axis Technology Integration Partner](https://www.axis.com/partner/technology-integration-partner-program) program. If you're not a partner, you can apply for access to the ACAP Service Portal if you qualify for the program requirements.

To sign your application, you'll need to set some fields in the [manifest](../develop/application-project-structure#manifest-file-content), such as **vendor** and **architecture**. A full list of requirements and other information can be found in the [ACAP Service Portal](acap-service-portal).

### Verifying the signature

With [AXIS OS 9.20](https://help.axis.com/en-us/axis-os-release-notes#active-2019-9-20) and later, the Axis device verifies the signature of a signed ACAP application on installation. Applications without a signature are still supported. The signature is fully backward compatible, i.e. a signed application can be installed on a device with an AXIS OS version earlier than 9.20, in which case the device doesn't verify the application.

### Only allow signed applications

With [AXIS OS 11.2](https://help.axis.com/en-us/axis-os-release-notes#axis-os-11-2), an [interface is added to VAPIX](https://www.axis.com/vapix-library/subjects/t10102231/section/t10036126/display?section=t10036126-t10185050) to control whether an Axis device only accepts signed ACAP applications or not, improving the device's security posture.

| AXIS OS      | Signing requirement (default value) | Change signing requirement |
| ------------ | ------------- | ----------- |
| 9.20 - 11.1  | Both signed and unsigned applications are allowed to be installed. | Not possible to change. |
| 11.2 - 11.11 | Both signed and unsigned applications are allowed to be installed. | The VAPIX interface can be used to configure the device to only allow signed applications. |

Axis recommends that you allow unsigned applications to be installed during the
development of your ACAP application.

#### Planned changes

With AXIS OS 12.0, the default value is planned to change to only allow signed
applications by default. For more information regarding the reasoning for this
change, see the [article](https://www.axis.com/developer-community/news/axis-os-root-acap-signing)
on Developer Community.

The VAPIX interface introduced in AXIS OS 11.2 is planned to be removed in a
future version of AXIS OS, only allowing signed ACAP applications to be
installed on a device.

| AXIS OS      | Signing requirement (default value) | Change signing requirement |
| ------------ | ------------- | ----------- |
| 12.0 -       | Only signed applications are allowed to be installed. | The VAPIX interface can be used to configure the device to allow both signed and unsigned applications. |
| Future       | Only signed applications are allowed to be installed. | Not possible to change, VAPIX interface removed. |

### Get help

For more information about ACAP application signing, please refer to the ACAP
Service Portal or contact Axis support.
