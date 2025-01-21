---
layout: page
title: Axis devices & compatibility
nav_order: 8
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
runtime features are available in the specific AXIS OS release. The
availability of APIs in AXIS OS depends on both the AXIS OS version and the
device itself since some APIs are only relevant for certain devices. For
example, the Video capture API is only available on devices with an image
sensor.

## SDK and device compatibility

Device compatibility differs depending on which SDK you want to use.

The *ACAP Native SDK* is supported on all products for the chips listed in the
[hardware compatibility](#acap-native-sdk-hardware-compatibility) table that support the minimum AXIS
OS version required. So, for this SDK it is important to make sure that
the selected product or products support the minimum required AXIS OS version.
See [software compatibility](#find-the-right-sdk-for-software-compatibility)
table.

For containerized applications using the ACAP Computer Vision solution, compatibility is limited to specific devices and AXIS OS versions. See the [ACAP Computer Vision solution compatibility](#acap-computer-vision-solution-compatibility) section for more details.

### ACAP Native SDK hardware compatibility

Chip        | Architecture
:---------- | :-----------
ARTPEC-6    | armv7hf
ARTPEC-7    | armv7hf
ARTPEC-8    | aarch64
ARTPEC-9    | aarch64
CV25        | aarch64
i.MX 6SoloX | armv7hf

See detailed information in the [product interface
guide](https://www.axis.com/developer-community/product-interface-guide).

### ACAP Computer Vision solution compatibility

> **Note:**
>
> - Support for containerized applications using `armv7hf` are no longer
>   supported after AXIS OS 11.11.

> **Note:**
>
> - New Axis products released on AXIS OS 12.x will not have container support.
> - [All products with existing container support](https://www.axis.com/support/tools/product-selector/shared/%5B%7B%22index%22%3A%5B10%2C0%5D%2C%22value%22%3A%22ARTPEC-8%22%7D%2C%7B%22index%22%3A%5B10%2C2%5D%2C%22value%22%3A%22Yes%22%7D%5D)
>   will be supported until end of 2031 when [AXIS OS 2026 LTS](https://help.axis.com/en-us/axis-os) reaches end of life.

To get a list of devices that are compatible with the ACAP Computer Vision
solution, you can use Axis [Product Selector](https://www.axis.com/support/tools/product-selector).

More than one filter can be combined in a search, for example in the **Hardware
platform** section it's possible to filter on:

- Products equipped with `DLPU` using the field **Compute capabilities**
- Products with `aarch64` by choosing `ARTPEC-8` in field **System-on-chip**
- Products with container support by checking the **Container support** checkbox.

For convenience, here are direct links to a few specific filters you can apply
to list supported products for `aarch64`:

- [Container support](https://www.axis.com/support/tools/product-selector/shared/%5B%7B%22index%22%3A%5B10%2C0%5D%2C%22value%22%3A%22ARTPEC-8%22%7D%2C%7B%22index%22%3A%5B10%2C2%5D%2C%22value%22%3A%22Yes%22%7D%5D)
- [Container + DLPU support](https://www.axis.com/support/tools/product-selector/shared/%5B%7B%22index%22%3A%5B10%2C0%5D%2C%22value%22%3A%22ARTPEC-8%22%7D%2C%7B%22index%22%3A%5B10%2C1%5D%2C%22value%22%3A%22DLPU%22%7D%2C%7B%22index%22%3A%5B10%2C2%5D%2C%22value%22%3A%22Yes%22%7D%5D)

## Find the right SDK for software compatibility

Choose the appropriate SDK version based on what AXIS OS version you want
supporting your ACAP application.

How do I know if my device supports a specific AXIS OS version? Please check
the web page for download of [device software](https://www.axis.com/support/device-software).

> **Device software** has previously been named **firmware**.

### ACAP Native SDK software compatibility

The **Image version** referred to in the table below is the Docker image
release tag available from Docker Hub:

- [ACAP Native SDK](https://hub.docker.com/r/axisecp/acap-native-sdk/tags)

The tag format is `<image-version>-<architecture>-<container-distribution>`.
An example of a tag is `axisecp/acap-native-sdk:12.0.0-aarch64-ubuntu24.04`
where `12.0.0` maps to the image version.

#### ACAP version 12 releases

ACAP Release | ACAP Native SDK Image version | Compatible with AXIS OS version
:------------| :---------------------------- | :-------------------------------------------
12.0         | 12.0.0                        | 12.0 and later until LTS
12.1         | 12.1.0                        | 12.1 and later until LTS
12.2         | 12.2.0                        | 12.2 and later until LTS

#### ACAP version 4 releases

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
4.15         | 1.15                          | 11.11 (LTS)

### ACAP Computer Vision solution software compatibility

> **Note:**
>
> - From AXIS OS 12.0, the ACAP Computer Vision SDK has been archived as its
>   components have been refactored: utility libraries and scripts are now
>   available in [ACAP Runtime](https://github.com/AxisCommunications/acap-runtime).
>   For usage of the new setup, see the [examples](https://github.com/AxisCommunications/acap-computer-vision-sdk-examples)
>   repository.

The following information and compatibility table are provided for reference
and to support legacy applications using versions prior to AXIS OS 12.0:

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
4.15         | 1.15                          | 11.11 (LTS)

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
