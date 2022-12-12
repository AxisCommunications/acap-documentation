---
layout: page
parent: Introduction
title: ACAP version 4 vs version 3
nav_order: 3
---

# ACAP version 4 vs version 3

There are both similarities and differences between the two generations.

## What's new in ACAP version 4?

* A new SDK tailored to computer vision applications.
* The descendant of ACAP SDK, called ACAP Native SDK, replaces many of the
  older APIs.
* Introduction of native ACAP applications with containers.

## What are the differences between ACAP version 3 SDK and ACAP version 4 Native SDK?

At the time of the ACAP version 4 launch, the two SDKs are very similar but as we will
actively develop the ACAP version 4 Native SDK and keep ACAP version 3 SDK in maintenance mode,
the differences are expected to increase.

### APIs

ACAP version 4 Native SDK does not include all APIs from ACAP version 3. Instead, it aims to
replace many of the APIs from ACAP version 3.

| API | Future in ACAP version 4? |
| :-- | :-- |
| **axHTTP** | Replaced by the web-server [example](https://github.com/AxisCommunications/acap-native-sdk-examples/tree/master/web-server) which describes how to achieve the same functionality. |
| **axParameter**<br>**axAudio** | Will get a new API in a later release. |
| **axPTZ**<br>**Serialport API** | Not yet decided, i.e. may be replaced or moved as is to Native SDK. |
| **axStorage**| Will not be moved to Native SDK. |
| **Old Capture API<br>(Media capture)** | Will not be moved to Native SDK. |

The complete list of APIs included in the Native SDK is found
[here](../api/native-sdk-api).

### Container ACAP applications

In ACAP version 4 the possibility to build native ACAP applications (`.eap`-files) that
make use of containers inside has been added. This way, a container application
can be installed the same way as any other ACAP version 3 application. See the
[container
example](https://github.com/AxisCommunications/acap-native-sdk-examples/tree/master/container-example)
on GitHub.

## Which products are supported for applications built with ACAP version 4?

Compatibility depends on many things but one minimum requirement for ACAP version 4 is
AXIS OS firmware 10.7. The web page [Axis devices and
compatibility](../axis-devices-and-compatibility) explains compatibility in more depth.
