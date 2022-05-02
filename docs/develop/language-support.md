---
layout: page
parent: Develop applications
title: Supported languages
nav_order: 8
---

# Supported languages

The [ACAP Native SDK](https://hub.docker.com/r/axisecp/acap-native-sdk) and [ACAP Computer Vision SDK](https://hub.docker.com/r/axisecp/acap-computer-vision-sdk) are capable of building applications in various languages.

## ACAP Native SDK

### C

Most of the examples are built using C and can be found in the [acap-native-sdk-examples](https://github.com/AxisCommunications/acap-native-sdk-examples) GitHub repository.
The SDK uses gcc to compile C programs.

### C++

To see an example of a C++ application, please see the [using-opencv](https://github.com/AxisCommunications/acap-native-sdk-examples/tree/master/using-opencv) example.
The SDK uses g++ to compile C++ programs.

### Shell script

The build process requires a Makefile, even if nothing is being compiled. An empty Makefile is necessary to build shell script programs. To see an example of a hello world application written in shell script using manifest, please see [shell-script-example](https://github.com/AxisCommunications/acap-native-sdk-examples/tree/master/shell-script-example).

## ACAP Computer Vision SDKs

### C++

Most of the example applications built on Python are also built on C++ and can be found in the [acap-computer-vision-sdk-examples](https://github.com/AxisCommunications/acap-computer-vision-sdk-examples) GitHub repository.
The SDK uses g++ to compile C++ programs.

### Python

Several examples are built using Python and can be found in the [acap-computer-vision-sdk-examples](https://github.com/AxisCommunications/acap-computer-vision-sdk-examples) GitHub repository.
