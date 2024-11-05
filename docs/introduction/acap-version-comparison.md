---
layout: page
parent: Introduction
title: ACAP version comparison
nav_order: 3
---

# ACAP version comparisons

## ACAP version 12

Starting with version 12.0, the ACAP release version and the ACAP Native SDK
version align with the major and minor of the [AXIS OS
versioning](https://help.axis.com/en-us/axis-os#axis-os-versioning) to provide
clearer compatibility mapping and simpler version tracking.

* ACAP version 12.0 contains acap-native-sdk 12.0.0 and maps to AXIS OS 12.0.

ACAP applications built with ACAP 12.0 will be forward compatible with all 12.x
releases where the last one in the series is the long-term support (LTS) release. After the
LTS release, planned breaking changes will be implemented which is indicated
with the step in major. The ACAP version major shows the LTS scope.

Note that the step in major from 4 to 12 is not marking a new generation with a
leap in technology or in the ACAP offering. This is a change from ACAP 3 and 4
releases that have had LTS scopes over multiple ACAP 4.x and 3.x releases, e.g.

* ACAP version 4.3 is LTS release and maps to AXIS OS 10.12 LTS.
* ACAP version 4.15 is LTS release and maps to AXIS OS 11.11 LTS.

## ACAP version 4 vs version 3

### What's new in ACAP version 4?

* A new SDK tailored to computer vision applications.
* The descendant of ACAP SDK, called ACAP Native SDK, replaces many of the
  older APIs.
* Introduction of native ACAP applications with containers.

### What are the differences between ACAP version 3 SDK and ACAP version 4 Native SDK?

At the time of the ACAP version 4 launch, the two SDKs are very similar, but we'll
actively develop the ACAP version 4 Native SDK while keeping the ACAP version 3 SDK in maintenance mode.

#### APIs

ACAP version 4 Native SDK does not include all APIs from ACAP version 3. Instead, it aims to
replace many of the APIs from ACAP version 3.

| API | Future in ACAP version 4? |
| :-- | :-- |
| **axHTTP** | Replaced by the [web-server](https://github.com/AxisCommunications/acap-native-sdk-examples/tree/main/web-server) and [web-server-using-fastcgi](https://github.com/AxisCommunications/acap-native-sdk-examples/tree/main/web-server-using-fastcgi) examples which describe how to achieve the same functionality. |
| **axSerialPort** | Added to ACAP Native SDK in 1.11 release as [Serial Port API](../api/native-sdk-api#serial-port-api). |
| **axStorage** | Added to ACAP Native SDK in 1.11 release as [Edge Storage API](../api/native-sdk-api#edge-storage-api). |
| **axParameter** | Added to ACAP Native SDK in 1.13 release as [Parameter API](../api/native-sdk-api#parameter-api). |
| **axAudio** | Will get a new API in a later release. |
| **axPTZ** | Not yet decided, i.e. may be replaced or moved as is to Native SDK. |
| **Old Capture API<br>(Media capture)** | Replaced by the [Video Capture API (VDO)](../api/native-sdk-api#video-capture-api-vdo). |

The complete list of APIs included in the Native SDK is found
[here](../api/native-sdk-api).

#### Container ACAP applications

In ACAP version 4 the possibility to build native ACAP applications (`.eap`-files) that
make use of containers inside has been added. This way, a container application
can be installed the same way as any other ACAP version 3 application. See the
[container
example](https://github.com/AxisCommunications/acap-native-sdk-examples/tree/main/container-example)
on GitHub.

### Which products are supported for applications built with ACAP version 4?

Compatibility depends on many things but one minimum requirement for ACAP version 4 is
AXIS OS firmware 10.7. The web page [Axis devices and
compatibility](../axis-devices-and-compatibility) explains compatibility in more depth.
