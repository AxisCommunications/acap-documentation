---
layout: acap_sdk_version_3
parent: Services for partners
grand_parent: ACAP SDK version 3
title: Accept or deny unsigned ACAP applications
nav_order: 3
redirect_to: https://developer.axis.com/acap/acap-sdk-version-3/services-for-partners/accept-or-deny-unsigned-acap-applications
---
# Accept or deny unsigned ACAP applications

> **Note**
> This feature requires ACAP SDK version 3.2 (firmware version 11.2).

You can use a toggle to configure an Axis device to accept signed packages only.

The signature verification is performed during the ACAP application installation.

> **Important**
>
> Any unsigned application that was installed while the toggle was set to accept unsigned packages, will still be installed after the toggle is set to not accept unsigned packages.

## Application API examples

Allow unsigned packages

```text
http://<servername>/axis-cgi/applications/config.cgi?action=set&name=AllowUnsigned&value=true
```

Deny unsigned packages

```text
http://<servername>/axis-cgi/applications/config.cgi?action=set&name=AllowUnsigned&value=false
```

Read the current configuration

```text
http://<servername>/axis-cgi/applications/config.cgi?action=get&name=AllowUnsigned
```
