---
layout: page
title: Native SDK API
parent: API
nav_order: 1
---

# Native SDK API

The ACAP Native SDK provides the following APIs:

- [Video capture API](#video-capture-api)
- [Machine learning API](#machine-learning-api)
- [Overlay API](#overlay-api)
- [Cairo](#cairo)
- [OpenCL](#opencl)
- [Event API](#event-api)
- [License Key API](#license-key-api)

## Compatibility

The table below shows ACAP Native SDK and firmware version compatibility.

SDK version | Available from firmware version
----------- | -------------------------------
1.0 | 10.7
1.1 | 10.9
1.2 | 10.10
1.3 | 10.12

## Video capture API

Go to the [ACAP API Documentation](src/api/vdostream/html/index.html) for detailed functional descriptions of this API.

The VdoStream API provides:

- video and image stream
- video and image capture
- video and image configuration

## Available video compression formats through VDO

The table below shows available subformats for corresponding YUV format.

Sub Formats | Corresponding format
----------- | -------------------------------
nv12 | YUV
y800 | YUV

An application to start a vdo stream can be found at [vdostream](https://github.com/AxisCommunications/acap-native-sdk-examples/tree/master/vdostream/), where the first argument is a string describing the video compression format. It takes `h264` (default), `h265`, `jpeg`, `nv12`, and `y800` as inputs. Both `nv12` and `y800` correspond to YUV format of VDO.

### Compatibility

The API supports products with the following chips:

- ARTPEC-8
- ARTPEC-7
- ARTPEC-6
- Ambarella S5L
- Ambarella S5

### Version history

The Video capture API was introduced in Native SDK 1.0.

### Known issues

- A memory leak in VDO was found in firmware versions from 10.10 for Artpec chips, later fixed in 10.11.65. The issue affects function `vdo_buffer_get_data`.

### Code Examples

- [vdostream](https://github.com/AxisCommunications/acap-native-sdk-examples/tree/master/vdostream/)
  - The example code is written in C which starts a vdo stream and then illustrates how to continuously capture frames from the vdo service, access the received buffer contents as well as the frame metadata.
- [vdo-larod](https://github.com/AxisCommunications/acap-native-sdk-examples/tree/master/vdo-larod/)
  - The example code is written in C and loads an image classification model to [larod](https://github.com/AxisCommunications/acap-native-sdk-examples/tree/master/FAQs.md#WhatisLarod?) and then uses vdo to fetch frames of size WIDTH x HEIGHT in yuv format which are converted to interleaved rgb format and then sent to larod for inference on MODEL.
- [vdo-larod-preprocessing](https://github.com/AxisCommunications/acap-native-sdk-examples/tree/master/vdo-larod-preprocessing/)
  - The example code is written in C and loads an image classification model to [larod](https://github.com/AxisCommunications/acap-native-sdk-examples/tree/master/FAQs.md#WhatisLarod?) and then uses vdo to fetch frames of size WIDTH x HEIGHT in yuv
  format which are sent to larod for preprocessing and inference on MODEL.
- [vdo-opencl-filtering](https://github.com/AxisCommunications/acap-native-sdk-examples/tree/master/vdo-opencl-filtering/)
  - This example illustrates how to capture frames from the vdo service, access the received buffer, and finally perform a GPU accelerated Sobel filtering with OpenCL.

## Machine learning API

Larod provides a simple unified C API for running machine learning and image preprocessing efficiently. Larod is open source on GitLab, see [Introduction to larod](https://gitlab.com/unimatrix/larod/-/blob/master/doc/introduction-for-app-developers.md)

Go to the [ACAP API Documentation](src/api/larod/html/index.html) for detailed functional descriptions of this API.

The Machine learning API can be used for deep learning applications.

### Compatibility

The Larod API supports products with the following chips:

- ARTPEC-8
- ARTPEC-7
- Ambarella S5L

For products with a DLPU (Deep Learning Processing Unit), inference runs on the DLPU otherwise it runs on the CPU.

### Version history

The Machine learning API was introduced in Native SDK 1.0.

### Code Examples

- [larod](https://github.com/AxisCommunications/acap-native-sdk-examples/tree/master/larod/)
  - The example code is written in C which connects to [larod](https://github.com/AxisCommunications/acap-native-sdk-examples/tree/master/FAQs.md#WhatisLarod?) and loads a model, runs inference on it and then finally deletes the loaded model from [larod](https://github.com/AxisCommunications/acap-native-sdk-examples/tree/master/FAQs.md#WhatisLarod?).
- [tensorflow-to-larod](https://github.com/AxisCommunications/acap-native-sdk-examples/tree/master/tensorflow-to-larod/)
  - This example covers model conversion, model quantization, image formats and custom models in greater depth than the [larod](https://github.com/AxisCommunications/acap-native-sdk-examples/tree/master/larod) and [vdo-larod](https://github.com/AxisCommunications/acap-native-sdk-examples/tree/master/vdo-larod) examples.
  - A separate example is available for [ARTPEC-8](https://github.com/AxisCommunications/acap-native-sdk-examples/tree/main/tensorflow-to-larod-artpec8) cameras.
- [object-detection](https://github.com/AxisCommunications/acap-native-sdk-examples/tree/master/object-detection/)
  - The example code focus on object detection, cropping and saving detected objects into JPEG files.
- [vdo-larod](https://github.com/AxisCommunications/acap-native-sdk-examples/tree/master/vdo-larod/)
  - The example code is written in C and loads an image classification model to [larod](https://github.com/AxisCommunications/acap-native-sdk-examples/tree/master/FAQs.md#WhatisLarod?) and then uses vdo to fetch frames of size WIDTH x HEIGHT in yuv format which are converted to interleaved rgb format
- [vdo-larod-preprocessing](https://github.com/AxisCommunications/acap-native-sdk-examples/tree/master/vdo-larod-preprocessing/)
  - The example code is written in C and loads an image classification model to [larod](https://github.com/AxisCommunications/acap-native-sdk-examples/tree/master/FAQs.md#WhatisLarod?) and then uses vdo to fetch frames of size WIDTH x HEIGHT in yuv
  format which are sent to larod for preprocessing and inference on MODEL.

## Overlay API

Go to the [ACAP API Documentation](src/api/axoverlay/html/index.html) for detailed functional descriptions of this API.

The Axoverlay API is a helper library that enables an ACAP to draw overlays in selected video streams. It has built-in support for Cairo as rendering API, as well as an open backend for any other custom rendering.

### Compatibility

The API supports products with the following chips:

- ARTPEC-8
- ARTPEC-7
- ARTPEC-6

### Version history

The Axoverlay API was introduced in Native SDK 1.0.

### Code Examples

- [axoverlay](https://github.com/AxisCommunications/acap-native-sdk-examples/tree/master/axoverlay/)
  - The example code is written in C which illustrates how to draw plain boxes and text as overlays in a stream.

## Cairo

Open-source rendering library for 2D vector graphics. See [Cairo documentation](https://www.cairographics.org/documentation/)

### Compatibility

The Cairo API supports products with the following chips:

- ARTPEC-8
- ARTPEC-7
- ARTPEC-6

### Version history

The Cairo API was introduced in Native SDK 1.0.

### Code Examples

- [axoverlay](https://github.com/AxisCommunications/acap-native-sdk-examples/tree/master/axoverlay/)
  - The example code is written in C which illustrates how to draw plain boxes and text as overlays in a stream.

## OpenCL

Accelerate parallel compute with GPU. See [OpenCL documentation](https://www.khronos.org/opencl/)

### Compatibility

The OpenCL API supports products with the following chips:

- ARTPEC-8
- ARTPEC-7

### Version history

The OpenCL 1.2 was introduced in Native SDK 1.0.

### Code Examples

- [vdo-opencl-filtering](https://github.com/AxisCommunications/acap-native-sdk-examples/tree/master/vdo-opencl-filtering/)
  - This example illustrates how to capture frames from the vdo service, access the received buffer, and finally perform a GPU accelerated Sobel filtering with OpenCL.

## Event API

Go to the [ACAP API Documentation](src/api/axevent/html/index.html) for detailed functional descriptions of this API.

The Axevent API provides:

- an interface to the event system found in Axis products.
- applications with a mechanism for sending and receiving events.

An application can both send and receive events.

### Event types

**Stateless (Pulse)** – An event that indicates that something has occurred. Typically used to trigger some action rule.

**Stateful (State)** – An event with an active and inactive state. Typically used in action rules like “record while active”.

**Data (Application Data)** – An event that includes data that needs to be processed by the consuming application such as transaction data, license plate or other dynamic data. A data event is normally not used to trigger generic action rules.

### Supported namespaces

When declaring events it is required to set a namespace. Following are the supported namespaces:

**tnsaxis** – Axis namespace to use with Axis events

**tns1** – ONVIF namespace to use with ONVIF events

### Compatibility

The API supports products with the following chips:

- ARTPEC-8
- ARTPEC-7
- ARTPEC-6
- Ambarella S5L
- Ambarella S5

### Version history

The Axevent API was introduced in Native SDK 1.0.

### Code Examples

- [send_event](https://github.com/AxisCommunications/acap-native-sdk-examples/tree/master/axevent/send_event)
  - The example code is written in C which sends an ONVIF event periodically.
- [subscribe_to_event](https://github.com/AxisCommunications/acap-native-sdk-examples/tree/master/axevent/subscribe_to_event)
  - The example code is written in C which subscribe to the ONVIF event sent from application "send_event".
- [subscribe_to_event_s](https://github.com/AxisCommunications/acap-native-sdk-examples/tree/master/axevent/subscribe_to_events)
  - The example code is written in C which subscribes to different predefined events.

## License Key API

Go to the [ACAP API Documentation](src/api/licensekey/html/index.html) for detailed functional descriptions of this API.

Use the License Key API to validate an application license key.

A license key is a signed file, generated for a specific device ID and application ID. The ACAP Service Portal maintains both license keys and application IDs.

### Compatibility

The API supports products with the following chips:

- ARTPEC-8
- ARTPEC-7
- ARTPEC-6
- Ambarella S5L
- Ambarella S5

### Version history

This API was introduced in API version 1.0

### Code Examples

- [licensekey](https://github.com/AxisCommunications/acap-native-sdk-examples/tree/master/licensekey/)
  - The example code is written in C which illustrates how to check the licensekey status.
