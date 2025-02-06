---
layout: acap_sdk_version_3
parent: Get started
grand_parent: ACAP SDK version 3
title: Compatibility
nav_order: 2
redirect_to: https://developer.axis.com/acap/acap-sdk-version-3/get-started/compatibility
---
# Compatibility

Compatibility means that if an ACAP application can be installed and run on a specific device, then the application is compatible with the device. Compatibility depends on both hardware and software (firmware).

## Hardware compatibility

ACAP is supported on a large portion of all Axis devices. For an ACAP application to be hardware compatible with a specific device, the application must be compiled using the SDK corresponding to the chip architecture in the device.

ACAP version 3 SDK is available for two different architectures, `armv7hf` (32 bit) and `aarch64` (64 bit).

## Software compatibility

An ACAP application is software compatible with an AXIS OS firmware if the APIs and other ACAP runtime features are available in the specific firmware release. The available APIs in a firmware depends on both the firmware version and the device itself since some APIs are only relevant for certain devices. For example, the Video capture API is only available on devices with an image sensor.

## Find the right SDK for hardware compatibility

Find the right SDK for the hardware architecture of the specific device or devices that you want to develop for.

| Chip | Architecture |
| ---- | ------------ |
| i.MX 6ULL | armv7hf |
| i.MX 6SoloX | armv7hf |
| ARTPEC-6 | armv7hf |
| ARTPEC-7 | armv7hf |
| ARTPEC-8 | aarch64 |
| S2E | armv7hf |
| S2L | armv7hf |
| S3L | armv7hf |
| S5 | aarch64 |
| S5L | aarch64 |

See detailed instruction in [Find out which SDK to use](../get-started/find-out-which-sdk-to-use.md).

## Find the right SDK for software compatibility

Choose the appropriate SDK version based on what firmware version you want supporting your ACAP application.

| SDK version | Compatible with firmware version |
| ----------- | -------------------------------- |
| SDK 3.0     | 9.70 and later |
| SDK 3.1     | 9.80 (LTS) and later |
| SDK 3.2     | 10.2 and later |
| SDK 3.3     | 10.5 and later |
| SDK 3.4     | 10.6 and later |
| SDK 3.5     | 10.9 and later |

### Forward compatibility

The ACAP application is forward compatible for the firmware related to a specific SDK version. This means that the application is compatible for the listed firmware version and future firmware versions until the next firmware LTS (Long Term Support). After an LTS, there may be breaking changes that breaks compatibility, for example when a deprecated API is removed. Breaking changes are always announced in advance.

An ACAP application built with an SDK that is based on an older firmware version should always work on a newer firmware version within the same LTS window.

### Feature growth between LTS releases

To get new features, always use the latest ACAP SDK release. A new feature could be, for example, a new version of an API.

New SDK versions between LTS releases always add functionality in a way that an ACAP application, built using a previous version, will still compile with the new version of the SDK.

Read more about AXIS OS release tracks and related information [here](https://www.axis.com/products/online-manual/00000).

### Supporting older firmware

If you want an ACAP application to be compatible with older firmware, you need to choose an SDK for an older firmware.
