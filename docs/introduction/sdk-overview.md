---
layout: page
parent: Introduction
title: ACAP SDK overview
nav_order: 4
---

# ACAP SDK for edge-based applications

AXIS Camera Application Platform (ACAP) version 4 contains two complementing SDKs addressing different needs, the ACAP Native SDK and the ACAP Computer Vision SDK.

### ACAP Native SDK

The ACAP Native SDK is targeted towards users that want to develop plug-in style, event generating applications that fit well into a VMS centric system. This SDK offers high performance by integrating closely with AXIS OS and hardware. Already existing ACAP users should feel at home using this SDK and migrating from previous version ACAP 3 to this SDK should be straightforward.

#### Main use cases ####

* Plug-in style applications generating events and meta-data in a VMS centric system.

* Extensions to the default camera feature set.

* Complement to the ACAP Computer Vision SDK for application components that need optimal performance.

#### Content #### 

See the [ACAP Native SDK repository documentation](https://github.com/AxisCommunications/acap-native-sdk) for details.

#### Support ####

ACAP Native SDK is supported by most Axis products from ARTPEC-6 and up. See more information in the section about [compatibility](../axis-devices).

### ACAP Computer Vision SDK

The ACAP Computer Vision SDK is targeted towards video analytics application developers running their application entirely or partially on an Axis device. New users that may not be well acquainted with developing applications for edge should still feel at home with the standard toolchain and well-known APIs that come with this SDK. Integration with backend server or cloud should be easy, supporting an application design where the benefits of combining edge-based computing with the more capable server/cloud can be achieved.

#### Main use cases ####

* Multi-component, system solutions enabled by containerized applications.
* Computer vision applications for any business segment.
* Integration with standard IT infrastructure and cloud platforms.

#### Content ####

See the [ACAP Computer Vision SDK repository documentation](https://github.com/AxisCommunications/acap-computer-vision-sdk) for details.

#### Support ####

ACAP Computer Vision SDK is supported by ARTPEC-7 and ARTPEC-8 based products with a DLPU. See more information in the section about [compatibility](../axis-devices).
