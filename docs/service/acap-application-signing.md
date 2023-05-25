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

To sign your ACAP application, you'll need access to the [ACAP Service Portal](acap-service-portal), which is currently restricted to members of the [Axis Technology Integration Partner (TIP)](https://www.axis.com/partner/technology-integration-partner-program) program. If you're not a partner, you can apply for access to the ACAP Service Portal if you qualify for the program requirements.

To sign your application, you'll need to set some fields in the [manifest](../develop/application-project-structure#manifest-file-content), such as **vendor** and **architecture**. A full list of requirements and other information can be found in the [ACAP Service Portal](acap-service-portal).

### Verifying the signature

With [AXIS OS 9.20](https://help.axis.com/en-us/axis-os-release-notes#active-2019-9-20) and later, the Axis device verifies the signature on installation. Applications without a signature are still supported. The signature is fully backward compatible, i.e. a signed application can be installed on a device with a firmware earlier than 9.20, in which case the device doesn't verify the application.

### Only allow signed applications

With [AXIS OS 11.2](https://help.axis.com/en-us/axis-os-release-notes#axis-os-11-2), an [interface is added to VAPIX](https://www.axis.com/vapix-library/subjects/t10102231/section/t10036126/display?section=t10036126-t10185050) to control whether an Axis device only accepts signed ACAP applications or not, improving the device's security posture. The default value allows both signed and unsigned applications to be installed, but the VAPIX interface enables you to configure the device to only allow signed applications. We recommend that you allow unsigned applications to be installed during the development of your ACAP application.

The interface introduced in AXIS OS 11.2 is planned to be removed in a future version of AXIS OS, only allowing signed ACAP applications to be installed on a device. For more information regarding the reasoning for this change, and its timeline, see the [article on Developer Community](https://www.axis.com/developer-community/news/axis-os-root-acap-signing).

For more information about ACAP application signing, please refer to the ACAP Service Portal or contact Axis support.
