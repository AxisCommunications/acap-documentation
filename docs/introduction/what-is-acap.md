---
layout: page
parent: Introduction
title: What is ACAP?
nav_order: 1
---

# What is ACAP?

AXIS Camera Application Platform (ACAP) is an open application platform from Axis. It provides a development platform for software-based solutions and systems built around Axis devices. ACAP is available for various types of Axis products such as cameras, speakers and intercoms.

ACAP makes it possible to develop applications for a wide range of use cases:

- Security and safety applications that improve surveillance systems and facilitate investigation.
- Business intelligence applications that improve business efficiency.
- Product feature plug-ins that add value beyond the Axis product's core functionality.
- Address customer specific use cases that can't be solved with off-the-shelf products.

## Key features

- Access to most common product features, including video, audio, the event system, I/O ports, PTZ control, and more.
- Enables hardware acceleration on specific functions such as image analysis computations and overlay graphics.
- Toolchain with support for multiple architectures to build applications for all ACAP-enabled Axis products.
- Documentation, tutorials and example applications for all APIs to kickstart your development.

## ACAP SDK Docker images

From ACAP version 3.1, the SDK format relies on the [Docker](https://www.docker.com/) toolchain, something we see many developers use to manage their software. An important advantage of using Docker is that the SDK can be decoupled from the underlying host operating system. This enables us to support development across all Docker capable platforms, including not only Linux, but also Windows and macOS. Docker also offers a rich set of tools to build and ship software.

If you're new to Docker and its many features, check out their [Getting Started guide](https://www.docker.com/get-started).

Find all ACAP SDK images on the [Axis organization account](https://hub.docker.com/u/axisecp) and follow the instructions in [Get started](../get-started) to start developing your ACAP using Docker and our containerized SDK.
