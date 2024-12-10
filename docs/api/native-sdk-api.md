---
layout: page
title: Native SDK API
parent: API
nav_order: 1
---

# Native SDK API

The ACAP Native SDK provides the following APIs:

<!-- markdownlint-disable MD033 -->
- [Axis APIs](#axis-apis)
  - [Edge storage API](#edge-storage-api)
  - [Event API](#event-api)
  - [License Key API](#license-key-api)
  - [Machine learning API (Larod)](#machine-learning-api-larod)
  - [Message Broker API](#message-broker-api) <a class="label label-blue">BETA</a>
  - [Overlay APIs](#overlay-apis)
    - [Axoverlay API](#axoverlay-api)
    - [Bounding Box API](#bounding-box-api)
  - [Parameter API](#parameter-api)
  - [Serial port API](#serial-port-api)
  - [Video capture API (VDO)](#video-capture-api-vdo)
- [Open Source APIs](#open-source-apis)
  - [Cairo](#cairo)
  - [Curl](#curl)
  - [FastCGI](#fastcgi)
  - [Jansson](#jansson)
  - [OpenCL](#opencl)
  - [OpenSSL](#openssl)
- [Supplementary APIs](#supplementary-apis)
  - [VAPIX access for ACAP](#vapix-access-for-acap)

## Compatibility

> APIs on this page list which chips they are supported on, but note that the
> underlying feature also needs to be found and supported on the product. For
> example, the Video capture API is only available on devices with an image
> sensor.

To find compatibility between ACAP Native SDK and AXIS OS version,
refer to [Find the right SDK for software compatibility](../axis-devices-and-compatibility/#find-the-right-sdk-for-software-compatibility).

# Axis APIs

## Edge storage API

Go to the [ACAP API Documentation](src/api/axstorage/html/index.html) for detailed functional descriptions of this API.

The Edge storage API allows the application to save and retrieve data on mounted storage devices such as SD cards and NAS (Network Attached Storage) units. An application can only modify its own files on the storage device.
An application can both send and receive events.

### Compatibility

The API is supported on products with the following chips:

- ARTPEC-8
- ARTPEC-7
- ARTPEC-6
- Ambarella CV25
- i.MX 6SoloX

### Version history

The Edge storage API was introduced in Native SDK 1.11.

### Code Examples

- [axstorage](https://github.com/AxisCommunications/acap-native-sdk-examples/tree/main/axstorage)
  - This application demonstrates the usage of axstorage APIs, offering the following functionality:
    - List configured storage devices.
    - Subscribe to events from all storage devices.
    - Set up and utilize all available/mounted storage devices.
    - Continuously write data to two files on all available storage devices.
    - Automatically release any unmounted storage devices.

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

The API is supported on products with the following chips:

- ARTPEC-8
- ARTPEC-7
- ARTPEC-6
- Ambarella CV25
- i.MX 6SoloX

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

The API is supported on products with the following chips:

- ARTPEC-8
- ARTPEC-7
- ARTPEC-6
- Ambarella CV25
- i.MX 6SoloX

### Version history

This API was introduced in Native SDK 1.0.

### Code Examples

- [licensekey](https://github.com/AxisCommunications/acap-native-sdk-examples/tree/main/licensekey/)
  - The example code is written in C which illustrates how to check the licensekey status.

## Machine learning API (Larod)

Go to the [ACAP API Documentation](src/api/larod/html/index.html) for detailed functional descriptions of this API.

Larod is a service provides a simple unified C API for running machine learning and image preprocessing efficiently. The purpose of Larod is to provide a unified API for all hardware platforms with very little overhead and to arbitrate between different processes (apps) requesting access to the same hardware.

### Compatibility

The Larod API is supported on products with the following chips:

- ARTPEC-8
- ARTPEC-7
- Ambarella CV25

For products with a DLPU (Deep Learning Processing Unit), inference runs on the DLPU otherwise it runs on the CPU.

### Version history

The Machine learning API was introduced in Native SDK 1.0. All larod API versions are available.

### Code Examples

- [vdo-larod](https://github.com/AxisCommunications/acap-native-sdk-examples/tree/main/vdo-larod/)
  - The example code is written in C and loads an image classification model to the [Machine learning API (Larod)](#machine-learning-api-larod) and then uses the [Video capture API (VDO)](#video-capture-api-vdo) to fetch frames of size WIDTH x HEIGHT in yuv format which are converted to interleaved rgb format and then sent to larod for inference on MODEL.
- [object-detection](https://github.com/AxisCommunications/acap-native-sdk-examples/tree/main/object-detection/)
  - The example code focus on object detection, cropping and saving detected objects into JPEG files.
  - A separate example is available for [CV25](https://github.com/AxisCommunications/acap-native-sdk-examples/tree/main/object-detection-cv25) cameras.

## Message Broker API

> This API is a [Beta version](./beta-api) and developers are encouraged to test and leave feedback.

> This API was formerly known as Metadata Broker.

Go to the [ACAP API Documentation](src/api/message-broker/html/index.html) for detailed
functional descriptions of this API.

The Message Broker API allows an ACAP application to consume metadata from
a producer in AXIS OS by subscribing to a `topic`.

The API implements the Publish/Subscribe messaging paradigm.

### Compatibility

The Message Broker API is supported on products with the following chips:

- ARTPEC-8
- ARTPEC-7
- Ambarella CV25

### Version history

The Message Broker API was introduced in Native SDK 1.13.

AXIS OS version | Message Broker API version | New functions added
-- | -- | --
11.9 | 0.23.2 | New topic `com.axis.analytics_scene_description.v0.beta`
11.11 | 0.26.5 | New topic `com.axis.consolidated_track.v1.beta`

### Code Examples

- [consume-scene-metadata](https://github.com/AxisCommunications/acap-native-sdk-examples/tree/main/message-broker/consume-scene-metadata)
  - The example is written in C and shows how to consume metadata stream
    **Analytics Scene Description**.

## Overlay APIs

### Axoverlay API

Go to the [ACAP API Documentation](src/api/axoverlay/html/index.html) for detailed functional descriptions of this API.

The Axoverlay API is a helper library that enables an ACAP to draw overlays in selected video streams. It has built-in support for Cairo as rendering API, as well as an open backend for any other custom rendering.

#### Compatibility

The API is supported on products with the following chips:

- ARTPEC-8
- ARTPEC-7
- ARTPEC-6

#### Version history

The Axoverlay API was introduced in Native SDK 1.0.

#### Code Examples

- [axoverlay](https://github.com/AxisCommunications/acap-native-sdk-examples/tree/main/axoverlay/)
  - The example code is written in C which illustrates how to draw plain boxes and text as overlays in a stream.

### Bounding Box API

Go to the [ACAP API Documentation](src/api/bbox/html/index.html) for detailed functional descriptions of this API.

The Bounding Box API allows for the simple drawing of boxes on a scene. It supports all new chips and utilizes the most optimized drawing mechanisms available for each chip.
This API is recommended for adding basic box overlays. For more advanced features, refer to the Axoverlay API.

#### Compatibility

The API is supported on products with the following chips:

- ARTPEC-8
- ARTPEC-7
- Ambarella CV25

#### Version history

The Bounding Box API was introduced in Native SDK 1.15.

#### Code Examples

- [bounding-box](https://github.com/AxisCommunications/acap-native-sdk-examples/tree/main/bounding-box)
  - An example in C that demonstrates how to portably draw burnt-in bounding boxes on selected video sources or channels.

## Parameter API

Go to the [ACAP API Documentation](src/api/axparameter/html/index.html) for
detailed functional descriptions of this API.

The AXParameter C library provides the following functionality:

- Read and modify **application parameters** stated in `manifest.json`.
- Add and remove **application parameters** in C code, in addition to the ones
  already defined in `manifest.json`.
- Set up **callbacks** so the application can act immediately on changes made
  to the **application parameters** via the
  [application settings web page](#application-settings-web-page) or VAPIX.
- Read **system parameters**.

**Application parameters** have the following properties:

- They are preserved when an application is restarted or upgraded.
- They are preserved when the device is restarted and when firmware is upgraded.
- They are displayed and possible to set in the
  [application settings web page](#application-settings-web-page).
- They can be read and modified using VAPIX API
  [param.cgi](https://www.axis.com/vapix-library/subjects/t10175981/section/t10036014/display).

> The application parameters are **not private** to the application, they can
> be:
>
> - *read* via VAPIX by a user with `operator` privileges.
> - *read* and *modified* via VAPIX by a user with `admin` privileges.
> - *read* and *modified* by another application if the application users belongs
>   to the same group.

### Application settings web page

The application settings web page can be used to modify **application
parameters**.

In the Axis device web page:

- Go to *Apps* tab
- Open the application options
- Click *Settings* to open a dialog where parameters can be set

Note that a reload of the web page is required to display values set from C code
or VAPIX.

### Compatibility

The Parameter API is supported on products with the following chips:

- ARTPEC-8
- ARTPEC-7
- ARTPEC-6
- Ambarella CV25
- i.MX 6SoloX

### Version history

The Parameter API was introduced in Native SDK 1.13.

### Code Examples

- [axparameter](https://github.com/AxisCommunications/acap-native-sdk-examples/tree/main/axparameter)
  - An example in C that demonstrates how to manage application-defined parameters, allowing you to add, remove, set, get, and register callback functions for parameter value updates.

## Serial port API

Go to the [ACAP API Documentation](src/api/axserialport/html/index.html) for detailed functional descriptions of this API.

The Serial port API allows the application to configure and control the external serial port on selected Axis products.

### Compatibility

- The API supports the following standards:
  - RS-232
  - RS-422
  - RS-485
- The API is product dependent since not all Axis products are equipped with a serial port.
- The API is supported on products with the following chips:
  - ARTPEC-8
  - ARTPEC-7

### Version history

The Serial port API was introduced in Native SDK 1.11.

### Code Examples

- [axserialport](https://github.com/AxisCommunications/acap-native-sdk-examples/tree/main/axserialport)
  - This example details the creation of an ACAP application utilizing the axserialport API, showcasing the following actions:
    - Enabling the serial port.
    - Configuring parameters using the API.
    - Establishing communication between two available ports in the Axis product using GLib IOChannel methods.

## Video capture API (VDO)

Go to the [ACAP API Documentation](src/api/vdostream/html/index.html) for detailed functional descriptions of this API.

The VdoStream API provides:

- video and image stream
- video and image capture
- video and image configuration

### Available video compression formats through VDO

The table below shows available subformats for corresponding YUV format.

Sub Formats | Corresponding format
----------- | -------------------------------
nv12 | YUV
y800 | YUV

An application to start a vdo stream can be found at [vdostream](https://github.com/AxisCommunications/acap-native-sdk-examples/tree/main/vdostream/), where the first argument is a string describing the video compression format. It takes `h264` (default), `h265`, `jpeg`, `nv12`, and `y800` as inputs. Both `nv12` and `y800` correspond to YUV format of VDO.

### Compatibility

The API is supported on products with the following chips:

- ARTPEC-8
- ARTPEC-7
- ARTPEC-6
- Ambarella CV25

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
11.4 | 9.41.16 | `vdo_channel_get_ex`
11.5 | 9.59.0 | -
11.6 | 9.78.12 | `vdo_stream_set_gop_length`, `vdo_error_is_resource_limitation`

### Known issues

- A memory leak in VDO was found in firmware versions from 10.10 for ARTPEC chips, later fixed in 10.11.65. The issue affects function `vdo_buffer_get_data`.

### Code Examples

- [vdostream](https://github.com/AxisCommunications/acap-native-sdk-examples/tree/main/vdostream/)
  - The example code is written in C which starts a vdo stream and then illustrates how to continuously capture frames from the vdo service, access the received buffer contents as well as the frame metadata.
- [vdo-larod](https://github.com/AxisCommunications/acap-native-sdk-examples/tree/main/vdo-larod/)
  - The example code is written in C and loads an image classification model to the [Machine learning API (Larod)](#machine-learning-api-larod) and then uses the [Video capture API (VDO)](#video-capture-api-vdo) to fetch frames of size WIDTH x HEIGHT in yuv format which are converted to interleaved rgb format and then sent to larod for inference on MODEL.
- [vdo-opencl-filtering](https://github.com/AxisCommunications/acap-native-sdk-examples/tree/main/vdo-opencl-filtering/)
  - This example illustrates how to capture frames from the vdo service, access the received buffer, and finally perform a GPU accelerated Sobel filtering with OpenCL.

# Open Source APIs

## Cairo

Open-source rendering library for 2D vector graphics. See [Cairo documentation](https://www.cairographics.org/documentation/).

### Compatibility

The Cairo API is supported on products with the following chips:

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

The OpenCL API is supported on products with the following chips:

- ARTPEC-8
- ARTPEC-7

### Version history

The OpenCL 1.2 was introduced in Native SDK 1.0.

### Code Examples

- [vdo-opencl-filtering](https://github.com/AxisCommunications/acap-native-sdk-examples/tree/main/vdo-opencl-filtering/)
  - This example illustrates how to capture frames from the vdo service, access the received buffer, and finally perform a GPU accelerated Sobel filtering with OpenCL.

## FastCGI

[FastCGI](https://wikipedia.org/wiki/FastCGI) is a protocol for interfacing interactive programs with a web server.

### Compatibility

The FastCGI API is supported on products with the following chips:

- ARTPEC-8
- ARTPEC-7
- ARTPEC-6
- Ambarella CV25
- i.MX 6SoloX

### Version history

The FastCGI API was introduced in Native SDK 1.6.

### Code Examples

- [web-server-using-fastcgi](https://github.com/AxisCommunications/acap-native-sdk-examples/tree/main/web-server-using-fastcgi)
  - This example is written in C and explains how to build an ACAP application that can handle HTTP requests sent to the Axis device, using the device's own web server and FastCGI.

## OpenSSL

Open-source library for general-purpose cryptography and secure communication. See [OpenSSL documentation](https://www.openssl.org/docs/).

### Compatibility

The OpenSSL API is supported on products with the following chips:

- ARTPEC-8
- ARTPEC-7
- ARTPEC-6
- Ambarella CV25
- i.MX 6SoloX

### Version history

The OpenSSL API was introduced in Native SDK 1.14.

### Code Examples

- [curl-openssl](https://github.com/AxisCommunications/acap-native-sdk-examples/tree/main/curl-openssl/)
  - The example code is written in C which illustrates how to use curl and OpenSSL to retrieve a file securely from an external server for e.g. [example.com](<https://www.example.com>)

## Jansson

Open-source library for for encoding, decoding and manipulating JSON data. See [Jansson documentation](https://jansson.readthedocs.io/en/latest/).

### Compatibility

The Jansson API is supported on products with the following chips:

- ARTPEC-8
- ARTPEC-7
- ARTPEC-6
- Ambarella CV25
- i.MX 6SoloX

### Version history

The Jansson API was introduced in Native SDK 1.14.

### Code Examples

- [`vapix`](https://github.com/AxisCommunications/acap-native-sdk-examples/tree/main/vapix/)
  - The example code is written in C which illustrates calling VAPIX API with JSON request and response from within an ACAP application.

## Curl

Open-source library for transferring data with URLs. See [curl documentation](https://curl.se/docs/). For proxy configuration see [Global device proxy](../develop/proxy).

### Compatibility

The curl API is supported on products with the following chips:

- ARTPEC-8
- ARTPEC-7
- ARTPEC-6
- Ambarella CV25
- i.MX 6SoloX

### Version history

The curl API was introduced in Native SDK 1.14.

### Code Examples

- [curl-openssl](https://github.com/AxisCommunications/acap-native-sdk-examples/tree/main/curl-openssl/)
  - The example code is written in C which illustrates how to use curl and OpenSSL to retrieve a file securely from an external server for e.g. [example.com](<https://www.example.com>)
- [`vapix`](https://github.com/AxisCommunications/acap-native-sdk-examples/tree/main/vapix/)
  - The example code is written in C which illustrates how ,using curl, an ACAP application can call [VAPIX APIs](https://www.axis.com/vapix-library/).

# Supplementary APIs

## VAPIX access for ACAP

ACAP applications can request for VAPIX service account credentials in runtime. With these credentials, the ACAP application can call a local virtual host to make VAPIX requests on the device. See [VAPIX access for ACAP](../develop/VAPIX-access-for-ACAP-applications).

### Code Examples

- [`vapix`](https://github.com/AxisCommunications/acap-native-sdk-examples/tree/main/vapix/)
  - The example code is written in C which illustrates how an ACAP application can call [VAPIX APIs](https://www.axis.com/vapix-library/).
