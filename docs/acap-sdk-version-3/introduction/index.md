---
layout: acap_sdk_version_3
parent: ACAP SDK version 3
title: Introduction
nav_order: 1
---
# Introduction

AXIS Camera Application Platform (ACAP) is Axis own open application platform. It provides a development platform for software-based solutions and systems built around Axis devices. It's available on various types of Axis products, and not only on our cameras.

ACAP makes it possible to develop applications for a wide range of applications:

- Security applications that improve surveillance systems and facilitate investigation.
- Business intelligence applications that improve business efficiency.
- Product feature plug-ins that add value beyond the Axis product's core functionality.

## Key features

AXIS Camera Application Platform SDK (ACAP SDK) provides:

- Full access to most common product features, including video, audio, the event system, I/O ports, PTZ control, and more.
- Enables hardware acceleration on specific functions such as image analysis computations, overlay graphics and more.
- Support for multiple architectures to build applications for all ACAP-enabled Axis products.
- Example applications for all APIs to kickstart your development.

## This is the ACAP SDK

The ACAP SDK consists of:

**ACAP SDK** – This Docker container image contains all tools for building and packaging an ACAP 3 application as well as API components (header and library files) needed for accessing different parts of the camera firmware. The toolchain and API images are also available as separate images, described below. This guide assumes that you are working with the combined image.

**ACAP Toolchain** – This Docker container image contains the tools, compilers and scripts required to build applications.

**ACAP API** – This Docker container image contains header files, libraries and other API components that you need when building an ACAP application.

## This is why we use Docker

From version 3.1, the SDK format relies on the [Docker](https://www.docker.com/) toolchain, something we see many developers use to manage their software. An important advantage of using Docker is that the SDK can be decoupled from the underlying host operating system. This enables us to support development across all Docker capable platforms, including not only Linux, but also Windows and macOS. Docker also offers a rich set of tools to build and ship software.

If you're new to Docker and its many features, check out their [Getting Started guide](https://www.docker.com/get-started).

Follow the instructions in [Get started](../get-started/) to start developing your ACAP application using Docker and our containerized SDK.
