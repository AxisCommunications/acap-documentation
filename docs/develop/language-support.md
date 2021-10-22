---
layout: page
parent: Develop applications
title: Supported languages
nav_order: 7
---

# Supported languages
The [ACAP Native SDK](https://hub.docker.com/r/axisecp/acap-native-sdk) is capable of building applications in various languages.

## Shell script
The build process requires a Makefile to be present, even if nothing is being compiled. Therefore an empty Makefile is necessary to build shell script programs.

## C
Most of the examples are built using C and can be found in the [acap-native-sdk-examples](https://github.com/AxisCommunications/acap-native-sdk-examples) GitHub repository.
The SDK uses gcc to compile C programs.

## C++
To see an example of a C++ application, please see the [using-opencv](https://github.com/AxisCommunications/acap-native-sdk-examples/tree/master/using-opencv) example.
The SDK uses g++ to compile C++ programs.
