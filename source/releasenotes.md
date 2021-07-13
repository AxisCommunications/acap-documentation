---
layout: page
title: Release notes
---
## ACAP 4 Beta 1 – July 13 2021
### Overview
This is the first ACAP 4 beta release (limited availability). It contains:
 * ACAP Computer Vision SDK 1.0 beta1(details below) 
 * ACAP Native SDK 1.0 beta1(details below)
 * First version of Docker Compose ACAP (details below)
 * First version of new documentation format
 * [Code examples]( https://github.com/AxisCommunications/acap-application-examples) for the Computer Vision SDK
### ACAP Computer Vision SDK
#### Supported architectures
 * 32 bit, see [Docker repo](https://hub.docker.com/repository/docker/axisecp/acap-native-sdk)
#### Compatibility
 * Products:
    * Q1615 MkIII
    * P3255 LVE
 * Firmware:
    * AXIS OS build version 21.27.3_1
#### Limitations

### ACAP Native SDK 
#### Supported architectures
 * 32 and 64 bit, see [Docker repo](https://hub.docker.com/repository/docker/axisecp/acap-computer-vision-sdk)
#### Compatibility
 * Products:
    * All products from ARTPEC-6
 * Firmware:
    * Minimum AXIS OS version: 10.6

* APIs supported in this release:
  * AxEvent
  * AxOverlay
  * Cairo
  * Larod
  * Licensekey
  * OpenCL
  * Vdo

### New tools
#### Docker Compose ACAP
 * Support for containerized applications as .eap files (classic ACAPs) with Docker compose. 
    * [Docker compose ACAP repository]( https://hub.docker.com/repository/docker/axisecp/docker-compose-acap)
    * [Code example]( https://github.com/AxisCommunications/acap-native-sdk-examples/tree/master/container-example)
