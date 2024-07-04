---
layout: page
title: Axis devices & compatibility
nav_order: 7
---

# Axis devices & compatibility

Compatibility means that if an ACAP application can be installed and run on a
specific device, then the ACAP application is compatible with the device.
Compatibility depends on both hardware and software.

## Hardware compatibility

ACAP applications are supported on a large portion of all Axis devices. For an
ACAP application to be hardware compatible with a specific device, it must be
compiled using the SDK corresponding to the chip architecture in the device.

## Software compatibility

An ACAP application is software compatible with AXIS OS if the APIs and other
ACAP Runtime features are available in the specific AXIS OS release. The
availability of APIs in AXIS OS depends on both the AXIS OS version and the
device itself since some APIs are only relevant for certain devices. For
example, the Video capture API is only available on devices with an image
sensor.

## SDK and device compatibility

Device compatibility differs depending on which SDK you want to use.

The *ACAP Computer Vision SDK* is supported on a limited set of devices.
So, for this SDK, it's important to select one of the products listed
in the [hardware compatibility](#acap-computer-vision-sdk-hardware-compatibility) section.

The *ACAP Native SDK* is supported on all products for the chips listed in the
[hardware compatibility](#acap-native-sdk-hardware-compatibility) table that support the minimum AXIS
OS version required. So, for this SDK it is important to make sure that
the selected product or products support the minimum required AXIS OS version.
See [software compatibility](#find-the-right-sdk-for-software-compatibility)
table.

### ACAP Computer Vision SDK hardware compatibility

To get a list of devices that are compatible with the ACAP Computer Vision SDK, you can use Axis [Product Selector](https://www.axis.com/support/tools/product-selector). In the left menu under **Hardware platform**, check the **Container support** checkbox.

More than one filter can be combined in a search, for example in the mentioned **Hardware platform** section it's also possible to filter on products equipped with `DLPU` using the field **Compute capabilities**.

For convenience, here are direct links to a few specific filters you can apply:

- [Container support](https://www.axis.com/support/tools/product-selector/shared/%5B%7B%22index%22%3A%5B4%2C2%5D%2C%22value%22%3A%22Yes%22%7D%5D)
- [DLPU support](https://www.axis.com/support/tools/product-selector/shared/%5B%7B%22index%22%3A%5B4%2C1%5D%2C%22value%22%3A%22DLPU%22%7D%5D)
- [Container + DLPU support](https://www.axis.com/support/tools/product-selector/shared/%5B%7B%22index%22%3A%5B4%2C1%5D%2C%22value%22%3A%22DLPU%22%7D%2C%7B%22index%22%3A%5B4%2C2%5D%2C%22value%22%3A%22Yes%22%7D%5D)

### ACAP Native SDK hardware compatibility

Chip        | Architecture
:---------- | :-----------
ARTPEC-6    | armv7hf
ARTPEC-7    | armv7hf
ARTPEC-8    | aarch64
CV25        | aarch64
i.MX 6SoloX | armv7hf
i.MX 6ULL   | armv7hf
S5          | aarch64
S5L         | aarch64

See detailed information in the [product interface
guide](https://www.axis.com/developer-community/product-interface-guide).

## Find the right SDK for software compatibility

Choose the appropriate SDK version based on what AXIS OS version you want
supporting your ACAP application.

How do I know if my device supports a specific AXIS OS version? Please check
the web page for download of [device software](https://www.axis.com/support/device-software).

> **Device Software** has previously been named **firmware**.

### ACAP Computer Vision SDK software compatibility

The **Image version** referred to in the table below is the Docker image
release tag available from Docker Hub:

- [ACAP Computer Vision SDK](https://hub.docker.com/r/axisecp/acap-computer-vision-sdk/tags)

The tag format is `<image-version>-<architecture>-<sdk_type>`.
In the tag examples below, `1.5` maps to the image version.

- `axisecp/acap-computer-vision-sdk:1.5-aarch64`
- `axisecp/acap-computer-vision-sdk:1.5-aarch64-devel`
- `axisecp/acap-computer-vision-sdk:1.5-aarch64-runtime`

ACAP Release | ACAP CV SDK Image version | Compatible with AXIS OS version
:------------| :---------------------------- | :-------------------------------------------
4.0          | 1.0                           | 10.7 and later
4.1          | 1.1                           | 10.9 and later
4.2          | 1.2                           | 10.10 and later
4.3          | 1.3                           | 10.12 (LTS)
4.4          | 1.4                           | 11.0 and later
4.5          | 1.5                           | 11.1 and later
4.6          | 1.6                           | 11.2 and later
4.7          | 1.7                           | 11.3 and later
4.8          | 1.8                           | 11.4 and later
4.9          | 1.9                           | 11.5 and later
4.10         | 1.10                          | 11.6 and later
4.11         | 1.11                          | 11.7 and later
4.12         | 1.12                          | 11.8 (breaking change)
4.13         | 1.13                          | 11.9 and later
4.14         | 1.14                          | 11.10 and later
4.15         | 1.15                          | 11.11 (planned LTS)

### ACAP Native SDK software compatibility

The **Image version** referred to in the table below is the Docker image
release tag available from Docker Hub:

- [ACAP Native SDK](https://hub.docker.com/r/axisecp/acap-native-sdk/tags)

The tag format is `<image-version>-<architecture>-<container-distribution>`.
An example of a tag is

- `axisecp/acap-native-sdk:1.5-aarch64-ubuntu22.04`

where `1.5` maps to the image version.

ACAP Release | ACAP Native SDK Image version | Compatible with AXIS OS version
:------------| :---------------------------- | :-------------------------------------------
4.0          | 1.0                           | 10.7 and later until LTS
4.1          | 1.1                           | 10.9 and later until LTS
4.2          | 1.2                           | 10.10 and later until LTS
4.3          | 1.3                           | 10.12 (LTS)
4.4          | 1.4                           | 11.0 and later until LTS
4.5          | 1.5                           | 11.1 and later until LTS
4.6          | 1.6                           | 11.2 and later until LTS
4.7          | 1.7                           | 11.3 and later until LTS
4.8          | 1.8                           | 11.4 and later until LTS
4.9          | 1.9                           | 11.5 and later until LTS
4.10         | 1.10                          | 11.6 and later until LTS
4.11         | 1.11                          | 11.7 and later until LTS
4.12         | 1.12                          | 11.8 and later until LTS
4.13         | 1.13                          | 11.9 and later until LTS
4.14         | 1.14                          | 11.10 and later until LTS
4.15         | 1.15                          | 11.11 (planned LTS)

## Forward compatibility

An ACAP application is forward compatible for the AXIS OS related to a specific
SDK version. This means that the ACAP application is compatible for the listed
AXIS OS version and future versions until the next AXIS OS LTS (Long Term
Support) version. After an LTS, there may be changes that break compatibility,
for example when a deprecated API is removed. Breaking changes are always
announced in advance.

An ACAP application built with an SDK that is based on an older AXIS OS version
should always work on a newer AXIS OS version within the same LTS window.

## Feature growth between LTS releases

To get new features, always use the latest ACAP SDK release. A new feature
could be, for example, a new version of an API.

New SDK versions between LTS releases always add functionality in a way that an
ACAP built using a previous version will still compile with the new version
of the SDK.

Read more about AXIS OS release tracks and related information
[here](https://www.axis.com/products/online-manual/00000).

## Supporting older AXIS OS

If you want an ACAP application to be compatible with older AXIS OS, you need
to choose an SDK for an older AXIS OS.

To support AXIS OS older than 10.7, build your ACAP application with
[ACAP version 3](https://help.axis.com/acap-3-developer-guide).

# Camera loan tool

Find information about [virtual
loan](https://www.axis.com/developer-community/axis-virtual-loan-tool).
