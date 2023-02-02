---
layout: page
title: Axis devices & compatibility
nav_order: 7
---

# Axis devices & compatibility

Compatibility means that if an ACAP can be installed and run on a specific
device, then the ACAP is compatible with the device. Compatibility depends on
both hardware and software (firmware).

## Hardware compatibility

ACAP is supported on a large portion of all Axis devices. For an ACAP to be
hardware compatible with a specific device, the ACAP must be compiled using the
SDK corresponding to the chip architecture in the device.

## Software compatibility

An ACAP is software compatible with an AXIS OS firmware if the APIs and other
ACAP runtime features are available in the specific firmware release. The availability of
APIs in a firmware depends on both the firmware version and the
device itself since some APIs are only relevant for certain devices. For
example, the Video capture API is only available on devices with an image
sensor.

## SDK and device compatibility

Device compatibility differs depending on which SDK you want to use.

The *ACAP Computer Vision SDK* is supported on a limited set of devices.
So, for this SDK, it's important to select one of the products listed
in the [hardware compatibility](#acap-computer-vision-sdk) table.

The *ACAP Native SDK* is supported on all products for the chips listed in the
[hardware compatibility](#acap-native-sdk) table that support the minimum AXIS
OS version required. So, for this SDK it is important to make sure that
the selected product or products support the minimum required AXIS OS version.
See [software compatibility](#find-the-right-sdk-for-software-compatibility)
table.

## Find the right SDK for hardware compatibility

Find the right SDK for the hardware architecture of the specific device or
devices that you want to develop for.

### ACAP Computer vision SDK

Product      | Chip     | Architecture
:----------- | :------- | :-----------
M3215-LVE    | ARTPEC-8 | aarch64
M4308-PLE    | ARTPEC-7 | armv7hf
P1468-LE     | ARTPEC-8 | aarch64
P3255-LVE    | ARTPEC-7 | armv7hf
P3265-LVE    | ARTPEC-8 | aarch64
Q1615 Mk III | ARTPEC-7 | armv7hf
Q1656        | ARTPEC-8 | aarch64
Q1715        | ARTPEC-7 | armv7hf
Q1798-LE     | ARTPEC-7 | armv7hf
Q3536-LVE    | ARTPEC-8 | aarch64

### ACAP Native SDK

Chip     | Architecture
:------- | :-----------
ARTPEC-6 | armv7hf
ARTPEC-7 | armv7hf
ARTPEC-8 | aarch64
CV25     | aarch64
S5       | aarch64
S5L      | aarch64

See detailed information in the [product interface
guide](https://www.axis.com/developer-community/product-interface-guide).

## Find the right SDK for software compatibility

Choose the appropriate SDK version based on what AXIS OS version you want
supporting your ACAP.

ACAP SDK version | Compatible with AXIS OS version
:--------------- | :----------
SDK 4.0          | 10.7 and later
SDK 4.1          | 10.9 and later
SDK 4.2          | 10.10 and later
SDK 4.3          | 10.12 and later
SDK 4.4          | 11.0 and later
SDK 4.5          | 11.1 and later
SDK 4.6          | 11.2 and later

How do I know if my device supports a specific AXIS OS version? Please check
[firmware releases for supported
products](https://www.axis.com/support/firmware).

## Forward compatibility

The ACAP is forward compatible for the firmware related to a specific SDK
version. This means that the ACAP is compatible for the listed firmware version
and future firmware versions until the next firmware LTS (Long Term Support).
After an LTS, there may be changes that break compatibility, for
example when a deprecated API is removed. Breaking changes are always announced
in advance.

An ACAP built with an SDK that is based on an older firmware version should
always work on a newer firmware version within the same LTS window.

## Feature growth between LTS releases

To get new features, always use the latest ACAP SDK release. A new feature
could be, for example, a new version of an API.

New SDK versions between LTS releases always add functionality in a way that an
ACAP built using a previous version will still compile with the new version
of the SDK.

Read more about AXIS OS release tracks and related information
[here](https://www.axis.com/products/online-manual/00000).

## Supporting older firmware

If you want an ACAP to be compatible with older firmware, you need to choose an
SDK for an older firmware.

To support firmware older than AXIS OS 10.7, build your ACAP application with
[ACAP version 3](https://help.axis.com/acap-3-developer-guide).

# Camera loan tool

Find information about [virtual
loan](https://www.axis.com/developer-community/axis-virtual-loan-tool).
