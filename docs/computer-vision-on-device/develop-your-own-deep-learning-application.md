---
layout: page
parent: Computer vision on device
title: Develop your own deep learning application
nav_order: 1
---


# Develop your own deep learning application

As a developer, you have the ability to build your own application and run it directly on an Axis device. This allows you to create custom applications tailored to your specific needs.

To accomplish this, you can build your application and package it as an ACAP (Axis Camera Application Platform) application. ACAP provides a framework for developing and deploying applications on Axis devices. You can learn more about ACAP applications in the [What is an ACAP?](../introduction/what-is-acap) documentation.

There are two SDKs (Software Development Kits) available for developing ACAP applications: the Native SDK and the Computer Vision SDK. Both SDKs enable you to build computer vision applications, but there are some differences between them.

The Native SDK allows you to build applications that run directly on the Axis device. It supports C/C++ programming languages. On the other hand, the Computer Vision SDK allows you to build applications that run in a Docker container deployed on the Axis device. It supports Python applications in addition to C/C++. For more details and a comprehensive overview of the ACAP SDKs, refer to the [ACAP SDK Overview](../introduction/acap-sdk-overview) documentation.

To get started, you can explore the examples of deep learning applications available in our GitHub repositories. The [acap-native-sdk-examples](https://github.com/AxisCommunications/acap-native-sdk-examples) repository contains examples that use the Native SDK to run deep learning applications directly on the Axis device. Examples such as [vdo-larod](https://github.com/AxisCommunications/acap-native-sdk-examples/tree/main/vdo-larod) and [object-detection](https://github.com/AxisCommunications/acap-native-sdk-examples/tree/main/object-detection) showcase the capabilities of the Native SDK.

Alternatively, the [acap-computer-vision-sdk-examples](https://github.com/AxisCommunications/acap-computer-vision-sdk-examples) repository contains examples that utilize the Computer Vision SDK to run deep learning applications in a Docker container on the Axis device. Examples like [minimal-ml-inference](https://github.com/AxisCommunications/acap-computer-vision-sdk-examples/tree/main/minimal-ml-inference) and [object-detector-python](https://github.com/AxisCommunications/acap-computer-vision-sdk-examples/tree/main/object-detector-python) demonstrate the capabilities of the Computer Vision SDK.

These examples demonstrate the usage of our [machine learning API](../api/native-sdk-api.md#machine-learning-api-larod) also called Larod. Larod is a C API that enables you to run deep learning models in the TensorFlow Lite format. In the case of Computer Vision SDK examples, the ACAP Runtime is used as an interface to the machine learning API. The ACAP Runtime, available in the [ACAP Runtime repository](https://github.com/AxisCommunications/acap-runtime), facilitates communication with the machine learning API from a Docker container, allowing you to use any programming language.

Before diving into the development of your application, we recommend that you continue reading the rest of the documentation to understand the advantages and limitations of deploying a deep learning model on an Axis device.

To learn more about Axis deep learning accelerators, please continue reading the [Axis deep learning accelerators](./axis-deep-learning-procesing-unit) documentation.
