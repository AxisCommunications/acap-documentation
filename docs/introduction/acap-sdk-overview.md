---
layout: page
parent: Introduction
title: ACAP SDK overview
nav_order: 4
---

# ACAP SDK overview

AXIS Camera Application Platform (ACAP) offers the capability of building edge-based applications.

## Summary

Here is a summary of the difference between Native SDK and Computer Vision solution:

| | Native SDK | Computer Vision solution (Deprecated) |
|--|--|--|
| Supported Products | (see the [full compatibility list](../axis-devices-and-compatibility/#acap-native-sdk-hardware-compatibility)) | (see the [full compatibility list](../axis-devices-and-compatibility/#acap-computer-vision-sdk-hardware-compatibility)) |
| Requirements | Minimum AXIS OS 10.7 | Minimum AXIS OS 10.7, SD card |
| Programming Languages | C/C++ | C/C++, Python, .NET <br />  (and other mainstream languages) |
| App Development | Docker | Docker |
| App Deployment | Web GUI or VAPIX API | Docker |
| Examples | [Native SDK examples](https://github.com/AxisCommunications/acap-native-sdk-examples) | [Computer Vision examples](https://github.com/AxisCommunications/acap-computer-vision-sdk-examples) |

## ACAP Native SDK

The ACAP Native SDK is targeted towards users that want to develop plug-in style, event generating applications that fit well into a VMS centric system. This SDK offers high performance by integrating closely with AXIS OS and hardware. Already existing ACAP users should feel at home using this SDK and migrating from previous version ACAP version 3 to this SDK should be straightforward.

Use the [ACAP Native SDK](https://github.com/AxisCommunications/acap-native-sdk) for building applications that run directly on Axis devices. This option is always applicable and fully supported.

### Main use cases

- Plug-in style applications generating events and metadata in a VMS centric system.
- Extensions to the default camera feature set.

### Content

See the [ACAP Native SDK repository documentation](https://github.com/AxisCommunications/acap-native-sdk) for details.

### Support

ACAP Native SDK is supported by most Axis products from ARTPEC-6 and up. See more information in the section about [compatibility](../axis-devices-and-compatibility).

## ACAP Computer Vision solution

> **Important:** The ACAP Computer Vision solution is deprecated from AXIS OS 12.0.
>
> - The deprecation of the ACAP Computer Vision solution only affects container applications.
>   It will still be possible to build and run analytics, computer vision and machine learning applications on Axis devices using
>   ACAP Native SDK. Examples can be found in the
>   [ACAP Native SDK examples](https://github.com/AxisCommunications/acap-native-sdk-examples) repository.
>   For more context about this transition, please visit the [Enhanced ACAP SDK news article](https://www.axis.com/developer-community/news/enhanced-acap-sdk).
> - `armv7hf` is no longer supported after AXIS OS 11.11.
> - `aarch64` will be supported until the end of the AXIS OS 12 LTS cycle.
>   After this period, the components of the Computer Vision solution will no longer
>   receive updates or support.
> - From AXIS OS 12.0, the artifact ACAP Computer Vision SDK in form of a
>   container image is removed and utility libraries and scripts have been
>   moved to [ACAP Runtime](https://github.com/AxisCommunications/acap-runtime).
>   This means that the ACAP Computer Vision SDK is no longer needed to run container applications.

The ACAP Computer Vision solution allows container applications to run on Axis devices. It offers flexibility in choice of programming languages and enables easy integration with backend servers or cloud services. This solution is particularly useful for developers who prefer working with containerized applications or require specific environments that are not available in the Native SDK.

Depending on your target AXIS OS version, you have the following options:

1. **ACAP Computer Vision Solution** (for AXIS OS 12.0 and later): Use the following components:
   - [Docker ACAP](https://github.com/AxisCommunications/docker-acap)
   - [Docker Compose ACAP](https://github.com/AxisCommunications/docker-compose-acap)
   - [ACAP Runtime](https://github.com/AxisCommunications/acap-runtime)
2. **ACAP Computer Vision SDK** (for AXIS OS versions prior to 12.0): Use the [ACAP Computer Vision SDK](https://github.com/AxisCommunications/acap-computer-vision-sdk) to build containerized applications that can connect to Axis APIs. Note that this SDK is deprecated and not available for AXIS OS 12.0 and later.

### Main use cases

- Multi-component, system solutions enabled by containerized applications.
- Applications requiring specific runtime environments or libraries not available in the Native SDK.
- Integration with standard IT infrastructure and cloud platforms.

### Content

See the [ACAP Computer Vision APIs](../api/computer-vision-sdk-apis) page for more details.

### Support

ACAP Computer Vision solution is supported on products with container support. See more information in the section about [compatibility](../axis-devices-and-compatibility/#acap-computer-vision-solution-compatibility).
