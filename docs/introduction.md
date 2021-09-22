---
layout: page
title: Introduction
nav_order: 2
---

# Introduction

## What is ACAP?

AXIS Camera Application Platform (ACAP) is an open application platform from Axis. It provides a development platform for software-based solutions and systems built around Axis devices. ACAP is available for various types of Axis products such as cameras, speakers and intercoms.

ACAP makes it possible to develop applications for a wide range of applications:

* Security and safety applications that improve surveillance systems and facilitate investigation.

* Business intelligence applications that improve business efficiency.

* Product feature plug-ins that add value beyond the Axis product's core functionality.

* Address customer specific use cases that cannot be solved with the off-the-shelf products.

### Key features

* Access to most common product features, including video, audio, the event system, I/O ports, PTZ control, and more.

* Enables hardware acceleration on specific functions such as image analysis computations and overlay graphics.

* Toolchain with support for multiple architectures to build applications for all ACAP-enabled Axis products.

* Documentation, tutorials and example applications for all APIs to kickstart your development.

### ACAP SDK Docker images

From ACAP version 3.1, the SDK format relies on the [Docker](https://www.docker.com/) toolchain, something we see many developers use to manage their software. An important advantage of using Docker is that the SDK can be decoupled from the underlying host operating system. This enables us to support development across all Docker capable platforms, including not only Linux, but also Windows 10 and MacOS X. Docker also offers a rich set of tools to build and ship software.

If you're new to Docker and its many features, check out their [Getting Started guide](https://www.docker.com/get-started). 

Find all ACAP SDK images on the [Axis organization account]( https://hub.docker.com/orgs/axisecp) and follow the instructions in [Get started](get-started) to start developing your ACAP using Docker and our containerized SDK.

## Version history

ACAP was introduced already in 2009 and is the world’s first camera-based video analytics platform. Over the years, the ACAP concept has gradually expanded allowing more types of applications, introducing new APIs and exposing more of the device hardware for analytics.

### Table of ACAP versions

| Version | Release year | Support | Details |
| ------- | ------------ | ------- | ------- |
| ACAP 4 | 2021 | Actively developed | See [release notes](releasenotes) in this documentation for more information |
| ACAP 3 | 2020 | Actively maintained | [ACAP 3 documentation](https://help.axis.com/acap-3-developer-guide) |
| ACAP 2 | 2014 | No maintenance. End of support: Q4 2021 | For older firmware and products see [ACAP 2 documentation](https://www.axis.com/developer-community/acap-sdk-v2) |
| ACAP 1 | 2009 | Deprecated | No maintenance |

## ACAP SDK for edge-based applications

ACAP version 4 contains two complementing SDKs addressing different needs, the ACAP Native SDK and the ACAP Computer Vision SDK.

### ACAP Native SDK

The ACAP Native SDK is targeted towards users that want to develop plug-in style, event generating applications that fit well into a VMS centric system. This SDK offers high performance by integrating closely with AXIS OS and hardware. Already existing ACAP users should feel at home using this SDK and migrating from previous version ACAP 3 to this SDK should be straightforward.

#### Main use cases ####

* Plug-in style applications generating events and meta-data in a VMS centric system.

* Extensions to the default camera feature set.

* Complement to the ACAP Computer Vision SDK for application components that need optimal performance.

#### Content #### 

See the [ACAP Native SDK repository documentation]( https://github.com/AxisCommunications/acap-native-sdk) for details.

#### Support ####

ACAP Native SDK is supported by most Axis products from ARTPEC-6 and up. See more information in the section about [compatibility](axis-devices).

### ACAP Computer Vision SDK

The ACAP Computer Vision SDK is targeted towards video analytics application developers running their application entirely or partially on an Axis device. New users that may not be well acquainted with developing applications for edge should still feel at home with the standard toolchain and well-known APIs that come with this SDK. Integration with backend server or cloud should be easy, supporting an application design where the benefits of combining edge-based computing with the more capable server/cloud can be achieved.

#### Main use cases ####

* Multi-component, system solutions enabled by containerized applications.
* Computer vision applications for any business segment.
* Integration with standard IT infrastructure and cloud platforms.

#### Content ####

See the [ACAP Computer Vision SDK repository documentation]( https://github.com/AxisCommunications/acap-computer-vision-sdk) for details.

#### Support ####

ACAP Computer Vision SDK is supported by ARTPEC-7 based products with a DLPU. See more information in the section about [compatibility](axis-devices).

## ACAP examples

There are several ACAP code examples and tutorials available with an open-source license for both the ACAP Native SDK and ACAP Computer Vision SDK. Each example has a well-defined README file and example structure which will help you execute the examples on an Axis camera. The README file structure is comprised of:

* example description
* repository structure
* limitation
* how to build and run the code
* expected output

We are continuously adding new examples and tutorials for both existing as well as for new functionality. Keep checking the Axis [GitHub repo](https://github.com/AxisCommunications) to stay updated with the latest changes.

## Integration with other systems

A network camera is, more often than not, part of a solution that aims towards solving a specific use case. You might wish to send commands to the camera, or the camera is controlling another device via one of its I/O ports, or data generated on the camera should be sent over the network to an endpoint that aggregates data from multiple devices? In any of these circumstances we need to create the integration between the camera and its counterpart. And easy integration is key for any successful project that involved more than one part.

This chapter aims to describe various integrations, hopefully covering relevant parts of your solution.

### Integration with cloud

Some use cases will require an integration with the cloud. You might be building a cloud application that reads data streams, and wish to send data generated on the camera to this application? Or you might wish to send an image from the camera when an event is triggered? For those, or other, situation we can provide you with sample examples, serving as building blocks in your solution. We currently have repositories on GitHub, tailored towards the following cloud vendors.

- [Amazon Web Services (AWS)](https://github.com/AxisCommunications/acap-integration-examples-aws) - Integration between Axis devices and Amazon Web Services (AWS)
- [Microsoft Azure](https://github.com/AxisCommunications/acap-integration-examples-azure) - Integration between Axis devices and Microsoft Azure
- [Google Cloud Platform (GCP)](https://github.com/AxisCommunications/acap-integration-examples-gcp) - Integration between Axis devices and Google Cloud Platform (GCP)

If you find yourself wishing there was another example more relevant to your use case, please don't hesitate to start a discussion or open a new issue in the relevant GitHub repository.
