---
layout: page
title: Native SDK API
parent: API
nav_order: 1
---

# Native SDK API

The ACAP Native SDK provides the following APIs:

- [Video capture API (VDO)](#video-capture-api-vdo)
- [Machine learning API (Larod)](#machine-learning-api-larod)
- [Overlay API](#overlay-api)
- [Cairo](#cairo)
- [OpenCL](#opencl)
- [Event API](#event-api)
- [License Key API](#license-key-api)
- [FastCGI](#fastcgi)

## Compatibility

The table below shows ACAP Native SDK and firmware version compatibility.

SDK version | Available from firmware version
----------- | -------------------------------
1.0 | 10.7
1.1 | 10.9
1.2 | 10.10
1.3 | 10.12
1.4 | 11.0
1.5 | 11.1
1.6 | 11.2
1.7 | 11.3

## Video capture API (VDO)

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

An application to start a vdo stream can be found at [vdostream](https://github.com/AxisCommunications/acap-native-sdk-examples/tree/main/vdostream/), where the first argument is a string describing the video compression format. It takes `h264` (default), `h265`, `jpeg`, `nv12`, and `y800` as inputs. Both `nv12` and `y800` correspond to YUV format of VDO.

### Compatibility

The API supports products with the following chips:

- ARTPEC-8
- ARTPEC-7
- ARTPEC-6
- Ambarella CV25
- Ambarella S5L
- Ambarella S5

#### Compatibility limitations

- **Global rotation** - All platforms except ARTPEC-6 support global image source rotation, this feature is designed to utilize the hardware more efficiently. When designing applications for multiple platforms this needs to be taken into consideration. The Video capture API on ARTPEC-6 allows specifying the desired rotation per stream in contrast to other chips where this is a global option chosen at camera installation time and any attempt to specify capture rotation will be ignored.

### Version history

The Video capture API was introduced in Native SDK 1.0.

AXIS OS version | VdoStream API version | New functions added
-- | -- | --
10.7 | 6.13.0 | `vdo_frame_take_chunk`
10.8 | 6.24.1 | `vdo_zipstream_profile_get_type`, `vdo_frame_set_header_size`
10.9 | 6.34.16 | `vdo_stream_get_event`,`vdo_stream_get_event_fd`, `vdo_map_swap`
10.10 | 7.5.22 | `vdo_frame_take_chunk`, `vdo_frame_take_chunk_ex`, `vdo_stream_play`
10.11 | 7.19.2 | -
10.12 | 8.0.15 | `vdo_map_get_pair32i`, `vdo_map_get_pair32u`, `vdo_map_set_pair32i`, `vdo_map_set_pair32u`
11.0 | 9.0.4 | -
11.1 | 9.8.16 | -
11.2 | 9.18.0 | -
11.3 | 9.32.0 | -

### Known issues

- A memory leak in VDO was found in firmware versions from 10.10 for Artpec chips, later fixed in 10.11.65. The issue affects function `vdo_buffer_get_data`.

### Code Examples

- [vdostream](https://github.com/AxisCommunications/acap-native-sdk-examples/tree/main/vdostream/)
  - The example code is written in C which starts a vdo stream and then illustrates how to continuously capture frames from the vdo service, access the received buffer contents as well as the frame metadata.
- [vdo-larod](https://github.com/AxisCommunications/acap-native-sdk-examples/tree/main/vdo-larod/)
  - The example code is written in C and loads an image classification model to [larod](https://github.com/AxisCommunications/acap-native-sdk-examples/tree/main/FAQs.md#WhatisLarod?) and then uses vdo to fetch frames of size WIDTH x HEIGHT in yuv format which are converted to interleaved rgb format and then sent to larod for inference on MODEL.
- [vdo-larod-preprocessing](https://github.com/AxisCommunications/acap-native-sdk-examples/tree/main/vdo-larod-preprocessing/)
  - The example code is written in C and loads an image classification model to [larod](https://github.com/AxisCommunications/acap-native-sdk-examples/tree/main/FAQs.md#WhatisLarod?) and then uses vdo to fetch frames of size WIDTH x HEIGHT in yuv
  format which are sent to larod for preprocessing and inference on MODEL.
- [vdo-opencl-filtering](https://github.com/AxisCommunications/acap-native-sdk-examples/tree/main/vdo-opencl-filtering/)
  - This example illustrates how to capture frames from the vdo service, access the received buffer, and finally perform a GPU accelerated Sobel filtering with OpenCL.

## Machine learning API (Larod)

Go to the [ACAP API Documentation](src/api/larod/html/index.html) for detailed functional descriptions of this API.

Larod is a service provides a simple unified C API for running machine learning and image preprocessing efficiently. The purpose of Larod is to provide a unified API for all hardware platforms with very little overhead and to arbitrate between different processes (apps) requesting access to the same hardware.

### Compatibility

The Larod API supports products with the following chips:

- ARTPEC-8
- ARTPEC-7
- Ambarella CV25
- Ambarella S5L

For products with a DLPU (Deep Learning Processing Unit), inference runs on the DLPU otherwise it runs on the CPU.

### Version history

The Machine learning API was introduced in Native SDK 1.0. All larod API versions are available.

### Code Examples

- [larod](https://github.com/AxisCommunications/acap-native-sdk-examples/tree/main/larod/)
  - The example code is written in C which connects to [larod](https://github.com/AxisCommunications/acap-native-sdk-examples/tree/main/FAQs.md#WhatisLarod?) and loads a model, runs inference on it and then finally deletes the loaded model from [larod](https://github.com/AxisCommunications/acap-native-sdk-examples/tree/main/FAQs.md#WhatisLarod?).
- [tensorflow-to-larod](https://github.com/AxisCommunications/acap-native-sdk-examples/tree/main/tensorflow-to-larod/)
  - This example covers model conversion, model quantization, image formats and custom models in greater depth than the [larod](https://github.com/AxisCommunications/acap-native-sdk-examples/tree/main/larod) and [vdo-larod](https://github.com/AxisCommunications/acap-native-sdk-examples/tree/main/vdo-larod) examples.
  - A separate example is available for [ARTPEC-8](https://github.com/AxisCommunications/acap-native-sdk-examples/tree/main/tensorflow-to-larod-artpec8) cameras and [CV25](https://github.com/AxisCommunications/acap-native-sdk-examples/tree/main/tensorflow-to-larod-cv25) cameras.
- [object-detection](https://github.com/AxisCommunications/acap-native-sdk-examples/tree/main/object-detection/)
  - The example code focus on object detection, cropping and saving detected objects into JPEG files.
  - A separate example is available for [CV25](https://github.com/AxisCommunications/acap-native-sdk-examples/tree/main/object-detection-cv25) cameras.
- [vdo-larod](https://github.com/AxisCommunications/acap-native-sdk-examples/tree/main/vdo-larod/)
  - The example code is written in C and loads an image classification model to [larod](https://github.com/AxisCommunications/acap-native-sdk-examples/tree/main/FAQs.md#WhatisLarod?) and then uses vdo to fetch frames of size WIDTH x HEIGHT in yuv format which are converted to interleaved rgb format
- [vdo-larod-preprocessing](https://github.com/AxisCommunications/acap-native-sdk-examples/tree/main/vdo-larod-preprocessing/)
  - The example code is written in C and loads an image classification model to [larod](https://github.com/AxisCommunications/acap-native-sdk-examples/tree/main/FAQs.md#WhatisLarod?) and then uses vdo to fetch frames of size WIDTH x HEIGHT in yuv format which are sent to larod for preprocessing and inference on MODEL.

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

- [axoverlay](https://github.com/AxisCommunications/acap-native-sdk-examples/tree/main/axoverlay/)
  - The example code is written in C which illustrates how to draw plain boxes and text as overlays in a stream.

## Cairo

Open-source rendering library for 2D vector graphics. See [Cairo documentation](https://www.cairographics.org/documentation/).

### Compatibility

The Cairo API supports products with the following chips:

- ARTPEC-8
- ARTPEC-7
- ARTPEC-6

### Version history

The Cairo API was introduced in Native SDK 1.0.

### Code Examples

- [axoverlay](https://github.com/AxisCommunications/acap-native-sdk-examples/tree/main/axoverlay/)
  - The example code is written in C which illustrates how to draw plain boxes and text as overlays in a stream.

## OpenCL

Accelerate parallel compute with GPU. See [OpenCL documentation](https://www.khronos.org/opencl/).

### Compatibility

The OpenCL API supports products with the following chips:

- ARTPEC-8
- ARTPEC-7

### Version history

The OpenCL 1.2 was introduced in Native SDK 1.0.

### Code Examples

- [vdo-opencl-filtering](https://github.com/AxisCommunications/acap-native-sdk-examples/tree/main/vdo-opencl-filtering/)
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
- Ambarella CV25
- Ambarella S5L
- Ambarella S5

### Version history

The Axevent API was introduced in Native SDK 1.0.

### Code Examples

- [send_event](https://github.com/AxisCommunications/acap-native-sdk-examples/tree/main/axevent/send_event)
  - The example code is written in C which sends an ONVIF event periodically.
- [subscribe_to_event](https://github.com/AxisCommunications/acap-native-sdk-examples/tree/main/axevent/subscribe_to_event)
  - The example code is written in C which subscribe to the ONVIF event sent from application "send_event".
- [subscribe_to_events](https://github.com/AxisCommunications/acap-native-sdk-examples/tree/main/axevent/subscribe_to_events)
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
- Ambarella CV25
- Ambarella S5L
- Ambarella S5

### Version history

This API was introduced in Native SDK 1.0.

### Code Examples

- [licensekey](https://github.com/AxisCommunications/acap-native-sdk-examples/tree/main/licensekey/)
  - The example code is written in C which illustrates how to check the licensekey status.

## FastCGI

[FastCGI](https://wikipedia.org/wiki/FastCGI) is a protocol for interfacing interactive programs with a web server.

### Compatibility

The FastCGI API supports products with the following chips:

- ARTPEC-8
- ARTPEC-7
- CV25

### Version history

The FastCGI API was introduced in Native SDK 1.6.

### Code Examples

- [web-server-using-fastcgi](https://github.com/AxisCommunications/acap-native-sdk-examples/tree/main/web-server-using-fastcgi)
  - This example is written in C and explains how to build an ACAP application that can handle HTTP requests sent to the Axis device, using the device's own web server and FastCGI.
