---
layout: acap_container_applications_deprecation_page
parent: Develop container applications
title: Supported languages
nav_order: 3
redirect_to: https://developer.axis.com/acap/develop-container-applications/supported-languages
---

# Supported languages

## Python

All containerized ACAP application examples are built using Python and can be
found in the
[acap-computer-vision-sdk-examples](https://github.com/AxisCommunications/acap-computer-vision-sdk-examples)
GitHub repository.

## Other languages

> **Note**
>
> These are pointers to what could work but has not been tested and is not
> supported.

The ACAP Computer Vision solution offers flexibility in language choice. Users
are free to implement their applications in any programming language supported
by their chosen container environment.

A challenge however is to make use of [Axis
APIs](../api/computer-vision-sdk-apis) like Video Capture API and Machine
Learning API. In theory it should be possible by compiling protofiles for the
language of interest. [ACAP
runtime](https://github.com/AxisCommunications/acap-runtime) compiles
protofiles for Python and could give some leads to how it can be done for other
languages.
