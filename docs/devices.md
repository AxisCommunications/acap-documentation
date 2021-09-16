---
layout: page
title: Axis devices
nav_order: 10
---
## HW info
Compatibility means that if an ACAP can be installed and run on a specific device, then the ACAP is compatible with the device. Compatibility depends on both hardware and software (firmware).

### Hardware compatibility
ACAP is supported on a large portion of all Axis devices. For an ACAP to be hardware compatible with a specific device, the ACAP must be compiled using the SDK corresponding to the chip architecture in the device.

### Software compatibility
An ACAP is software compatible with an AXIS OS firmware if the APIs and other ACAP runtime features are available in the specific firmware release. The available APIs in a firmware depends on both the firmware version and the device itself since some APIs are only relevant for certain devices. For example, the Video capture API is only available on devices with an image sensor.

### Find the right SDK for hardware compatibility
Find the right SDK for the hardware architecture of the specific device or devices that you want to develop for.

Chip | Architecture
---- | ------------
ARTPEC-6 | armv7hf
ARTPEC-7 | armv7hf
S2E | armv7hf
S2L | armv7hf
S3L | armv7hf
S5 | aarch64
S5L | aarch64

See detailed information in the [product interface guide](https://www.axis.com/developer-community/product-interface-guide).

## Camera loan tool
Find information about [virtual loan](https://www.axis.com/developer-community/virtual-loan-tool).