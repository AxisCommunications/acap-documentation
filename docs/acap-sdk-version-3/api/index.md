---
layout: acap_sdk_version_3
parent: ACAP SDK version 3
title: API
nav_order: 6
---
# API

- [Audio API](#audio-api)
- [Video Capture API](#video-capture-api)
- [Media Capture API (deprecated)](#media-capture-api-deprecated)
- [Machine Learning API](#machine-learning-api)
- [Overlay API](#overlay-api)
- [Open standard APIs](#open-standard-apis)
- [Parameter API](#parameter-api)
- [HTTP API](#http-api)
- [Event API](#event-api)
- [Edge storage API](#edge-storage-api)
- [License API](#license-api)
- [Serial port API](#serial-port-api)
- [Pan tilt zoom API](#pan-tilt-zoom-api)

## Audio API

Go to the [ACAP API documentation](./src/api/axaudio/html/index.html) for detailed functional descriptions and examples of this API.

The Axaudio API allows the application to:

- retrieve compressed or uncompressed audio in different formats, from the camera
- send uncompressed audio to cameras with audio output
- configure sample rates and bitrates for some compressed formats

The API supports several get methods that returns supported formats for a camera or other audio product.

### Compatibility

The API supports products with the following chips:

- ARTPEC-8
- ARTPEC-7
- ARTPEC-6
- Ambarella CV25
- Ambarella S5L
- Ambarella S5
- Ambarella S2L
- i.MX 6SoloX
- i.MX 6ULL

### Version history

This API was introduced in API version earlier than 3.0.

## Video capture API

Go to the [ACAP API documentation](./src/api/vdostream/html/index.html) for detailed functional descriptions and examples of this API.

The VdoStream API provides:

- video and image stream
- video and image capture
- video and image configuration

### Compatibility

The API supports products with the following chips:

- ARTPEC-8
- ARTPEC-7
- ARTPEC-6
- Ambarella CV25
- Ambarella S5L
- Ambarella S5

#### Limitations

**Global rotation** – All platforms except ARTPEC-6 support global image source rotation. This feature is designed to utilize the hardware more efficiently. You need to take this into consideration when designing applications for multiple platforms. The Video capture API on ARTPEC-6 allows specifying the desired rotation per stream. For other chips this is a global option set when the camera is installed, and any attempt to specify capture rotation is ignored.

### Version history

The VdoStream API was introduced in API version 3.0.

| AXIS OS version | VdoStream API version | New functions added |
| --------------- | --------------------- | ------------------- |
| 10.2 | 2.3.13 | `vdo_stream_snapshot`<br>`vdo_stream_set_framerate`<br>`vdo_channel_get_filtered`|
| 10.3 | 3.0.0 | - |
| 10.4 | 4.0.12 | `vdo_buffer_get_id`|
| 10.5 | 5.0.25 | - |
| 10.6 | 5.9.14 | `vdo_channel_set_framerate`|
| 10.7 | 6.13.0 | `vdo_frame_take_chunk`|
| 10.8 | 6.24.1 | `vdo_zipstream_profile_get_type`<br>`vdo_frame_set_header_size`|
| 10.9 | 6.34.16 | `vdo_stream_get_event`<br>`vdo_stream_get_event_fd`<br>`vdo_map_swap` |
| 10.10 | 7.5.22 | `vdo_frame_take_chunk`<br>`vdo_frame_take_chunk_ex`<br>`vdo_stream_play`|
| 10.11 | 7.19.2 | - |
| 10.12 | 8.0.15 | `vdo_map_get_pair32i`<br>`vdo_map_get_pair32u`<br>`vdo_map_set_pair32i`<br>`vdo_map_set_pair32u` |
| 11.0 | 9.0.4 | - |

### Known issues

VdoStream has a memory leak in products with an ARTPEC chip using firmware version 10.10 or later. The issue was fixed in firmware version 10.11.65. The issue affects the `vdo_buffer_get_data` function.

### Code examples

#### Capture video stream

This code example on [GitHub](https://github.com/AxisCommunications/acap3-examples/tree/master/vdostream) starts a vdo stream and then illustrates how to continuously capture frames from the vdo service, access the received buffer contents as well as the frame metadata.

#### libvdo and larod combined

This code example on [GitHub](https://github.com/AxisCommunications/acap3-examples/tree/master/vdo-larod) loads an image classification model to larod and then uses vdo to fetch frames of size WIDTH x HEIGHT in yuv format which are converted to interleaved rgb format and then sent to larod for inference on MODEL.

## Media Capture API (deprecated)

Go to the [ACAP API documentation](./src/api/capture/html/index.html) for detailed functional descriptions and examples of this API.

### Compatibility

The API supports products with the following chips:

- ARTPEC-7
- ARTPEC-6
- Ambarella S5L
- Ambarella S5
- Ambarella S3L
- Ambarella S2L

### Version history

Media Capture API was deprecated and removed in version 3.5.

## Machine learning API

Go to the [ACAP API documentation](./src/api/larod/html/index.html) for detailed functional descriptions and examples of this API.

Larod provides a simple unified C API for efficiently running machine learning and image preprocessing. The purpose of Larod is to provide a unified API for all hardware platforms with very little overhead and to arbitrate between different processes (apps) requesting access to the same hardware.

### Compatibility

The API supports products with the following chips:

- ARTPEC-8
- ARTPEC-7
- Ambarella CV25
- Ambarella S5L

For products with a DLPU (Deep Learning Processing Unit), inference runs on the DLPU otherwise it runs on the CPU.

### Version history

| Larod API version | ACAP API version | What's new |
| ----------------- | ---------------- | ---------- |
| 1.0 | 3.1 | Larod API introduced |
| 2.0 | 3.3 | - [Preprocessing functionality](./src/api/larod/html/md__opt_builder-doc_larod_doc_preprocessing.html)<br>- Handles TFLite when using firmware version 10.6 and later. |
| 3.0 | 3.5 | - The larodDevice struct replaces larodChip.<br>- Different handling of cache when using buffers. |

> **Note**
> We recommend using Larod version 2.0 or 3.0. Larod version 1.0 will soon be deprecated. To use Larod 1.0, define `LAROD_API_VERSION_1` in your application, see **Backward compatibility** in [Introduction to larod for app developers](./src/api/larod/html/md__opt_builder-doc_larod_doc_introduction-for-app-developers.html) for more information.

### Code examples

#### Extract and analyze output

This code example on [GitHub](https://github.com/AxisCommunications/acap3-examples/tree/master/larod) connects to larod and loads a model, runs inference on it and then finally deletes the loaded model from larod.

#### libvdo and larod combined

This code example on [GitHub](https://github.com/AxisCommunications/acap3-examples/tree/master/vdo-larod) loads an image classification model to larod and then uses vdo to fetch frames of size WIDTH x HEIGHT in yuv format which are converted to interleaved rgb format and then sent to larod for inference on MODEL.

## Overlay API

Go to the [ACAP API documentation](./src/api/axoverlay/html/index.html) for detailed functional descriptions and examples of this API.

The Axoverlay API is a helper library that enables an ACAP application to draw overlays in selected video streams. It has built-in support for Cairo as rendering API, as well as an open backend for any other custom rendering.

### Compatibility

The API supports products with the following chips:

- ARTPEC-8
- ARTPEC-7
- ARTPEC-6

### Version history

The Axoverlay API was introduced in API version 3.0.

### Code examples

#### Draw plain boxes and text

This code example on [GitHub](https://github.com/AxisCommunications/acap3-examples/tree/master/axoverlay) shows how to draw plain boxes and text as overlays in a stream with the Axoverlay API.

## Open standard APIs

| Name | Description | Use cases | Compatibility | Documentation |
| ---- | ----------- | --------- | ------------- | ------------- |
| Cairo 1.16.0 | - Open-source rendering library for 2D vector graphics.<br>- For use with Ax_Overlay. | - Rendering texts for internal text overlays.<br>- Rendering lines, bounding boxes or any vector shapes.<br>- Loading SVG. | - ARTPEC-8<br>- ARTPEC-7<br>- ARTPEC-6<br>- Ambarella CV25<br>- Ambarella S5L<br>- Ambarella S5<br>- Ambarella S3L<br>- Ambarella S2L | See [Cairo documentation](https://www.cairographics.org/documentation/) |
| OpenGL ES 2.0 | Accelerate graphics rendering with GPU. | - Rendering mask for Axis Live Privacy Shield.<br>- Rendering GUI for door camera with display information as PTZ or a street name. | - ARTPEC-8<br>- ARTPEC-7 | See [OpenGL ES documentation](https://www.khronos.org/opengles/) |
| OpenCL 1.2 | Accelerate parallel compute with GPU. | - Color conversion (e.g. as pre-processing for DL and analytics.<br>- Audio filter.<br>- Accelerates OpenCV. | - ARTPEC-8<br>- ARTPEC-7<br>Note: GPU is disabled on some devices due to memory limitations. | See [OpenCL documentation](https://www.khronos.org/opencl/) |
| OpenVX 1.0 | Accelerate computer vision with GPU. | - perspective transform (e.g. as pre-processing for DL and analytics).<br>- Non real-time DL. | - ARTPEC-8<br>- ARTPEC-7 | See [OpenVX documentation](https://www.khronos.org/openvx/) |

### Version history

The open standard APIs were introduced in API version 3.0.

## Parameter API

Go to the [ACAP API documentation](./src/api/axparameter/html/index.html) for detailed functional descriptions and examples of this API.

The AxParameter API allows the application to save data and application settings so that they are not lost during a restart or firmware upgrade of the Axis product.

AxParameter makes it possible to define callback functions that perform specific actions if a parameter is updated, for example if the user updates a parameter using the Axis product's web pages.

> **Note**
> Data that's only used and altered by the application should not be handled by AxParameter. Such data can instead be handled by, for example, GLib GKeyFile.

Parameters specific to the application can be pre-configured when the application is created or be added in runtime.

### Compatibility

The API supports products with the following chips:

- ARTPEC-8
- ARTPEC-7
- ARTPEC-6
- Ambarella CV25
- Ambarella S5L
- Ambarella S5
- Ambarella S3L
- Ambarella S2L
- i.MX 6SoloX
- i.MX 6ULL

### Version history

This API was introduced in API version earlier than 3.0.

## HTTP API

Go to the [ACAP API documentation](./src/api/axhttp/html/index.html) for detailed functional descriptions and examples of this API.

The AxHTTP API allows the application to act as a CGI. This is done through a socket transfer to the ACAP application. This is a useful way to provide a configuration API, or updated information from the ACAP application. The information or configuration can then be accessed in ACA through a page provided by the ACAP application.

### Compatibility

The API supports products with the following chips:

- ARTPEC-8
- ARTPEC-7
- ARTPEC-6
- Ambarella CV25
- Ambarella S5L
- Ambarella S5
- Ambarella S3L
- Ambarella S2L
- i.MX 6SoloX
- i.MX 6ULL

### Version history

This API was introduced in API version earlier than 3.0.

## Event API

Go to the [ACAP API documentation](./src/api/axevent/html/index.html) for detailed functional descriptions and examples of this API.

The Axevent API provides:

- an interface to the event system found in Axis products.
- applications with a mechanism for sending and receiving events.

An application can both send and receive events.

### Event types

- **Stateless (Pulse)** – An event that indicates that something has occurred. Typically used to trigger some action rule.
- **Stateful (State)** – An event with an active and inactive state. Typically used in action rules like "record while
active".
- **Data (Application Data)** – An event that includes data that needs to be processed by the consuming application such as transaction data, license plate or other dynamic data. A data event is normally not used to trigger generic action rules.

### Supported Namespaces

When declaring events it is required to set a namespace. Following are the supported namespaces:

- `tnsaxis` – Axis namespace to use with Axis events
- `tns1` – ONVIF namespace to use with ONVIF events

### Compatibility

The API supports products with the following chips:

- ARTPEC-8
- ARTPEC-7
- ARTPEC-6
- Ambarella CV25
- Ambarella S5L
- Ambarella S5
- Ambarella S3L
- Ambarella S2L
- i.MX 6SoloX
- i.MX 6ULL

### Version history

| Event API version | ACAP API version | What's new |
| ----------------- | ---------------- | ---------- |
| 1.0               | ACAP 2           | Event API introduced |
| 1.1               | 3.2              | New functions:<br>- ax_event_new2<br>- ax_event_get_time_stamp2|

> **Note**
>
> - `ax_event_new` and `ax_event_get_time_stamp` functions are marked as deprecated from ACAP API version 3.2 because they use [GTimeVal](https://developer.gnome.org/glib/stable/glib-Date-and-Time-Functions.html#GTimeVal), which is deprecated in glib. Use `ax_event_new2` and `x_event_get_time_stamp2` instead.
> - To prevent installation of an application (using the Event API) on unsupported firmware (version 10.2 and earlier), set `REQEMBDEVVERSION` to `2.18` (or higher) in `package.conf` or `manifest.json`.

### Code examples

#### Subscribe to and send event

This code example on [GitHub](https://github.com/AxisCommunications/acap3-examples/tree/master/axevent) illustrates both how to subscribe to different events and how to send an event.

## Edge storage API

Go to the [ACAP API documentation](./src/api/axstorage/html/index.html) for detailed functional descriptions and examples of this API.

The AxStorage API allows the application to save and retrieve data on mounted storage devices such as SD cards and NAS (Network Attached Storage) units. An application can only modify its own files on the storage device.

### Compatibility

The API supports products with the following chips:

- ARTPEC-8
- ARTPEC-7
- ARTPEC-6
- Ambarella CV25
- Ambarella S5L
- Ambarella S5
- Ambarella S3L
- Ambarella S2L
- i.MX 6SoloX
- i.MX 6ULL

### Version history

This API was introduced in API version earlier than 3.0.

## License API

Go to the [ACAP API documentation](./src/api/licensekey/html/index.html) for detailed functional descriptions and examples of this API.

Use the LicenseKey API to validate an application license key.

A license key is a signed file, generated for a specific device ID and application ID. The ACAP Service Portal maintains both license keys and application IDs.

### Compatibility

The API supports products with the following chips:

- ARTPEC-8
- ARTPEC-7
- ARTPEC-6
- Ambarella CV25
- Ambarella S5L
- Ambarella S5
- Ambarella S3L
- Ambarella S2L
- i.MX 6SoloX
- i.MX 6ULL

> **Note**
> For ACAP applications built using `manifest.json`, license key handling is supported from firmware version 10.6 and later.

### Version history

This API was introduced in API version earlier than 3.0.

### Code examples

#### Status of a license key

This code example on [GitHub](https://github.com/AxisCommunications/acap3-examples/tree/master/licensekey) shows how to check the status of a license key.

## Serial port API

Go to the [ACAP API documentation](./src/api/axserialport/html/index.html) for detailed functional descriptions and examples of this API.

The AxSerialPort API allows the application to configure and control the external serial port on selected Axis products.

### Compatibility

The API is product dependent since not all Axis products are equipped with a serial port.

The API supports the RS-232, RS-422 and RS-485 standard.

The API supports products with the following chips:

- ARTPEC-8
- ARTPEC-7

### Version history

This API was introduced in API version earlier than 3.0.

## Pan tilt zoom API

Go to the ACAP [API documentation](./src/api/axptz/html/index.html) for detailed functional descriptions and examples of this API.

The AxPTZ API allows the application to control the camera's pan, tilt and zoom movements, to interact with the PTZ control queue and to create and delete preset positions.

> **Important**
> The AXPTZ library is designed to be used with the GLib library. An application using the AXPTZ library must have a running GMainLoop.

> **Note**
> The AXPTZ library has an internal reference counter. If using the pattern: create library, create library, ..., call function, call function, ..., destroy library, destroy library, ..., the library will be thread safe. It is recommended to call the create and destroy functions once in the main thread of the application.

### Compatibility

The API supports products with the following chips:

- ARTPEC-8
- ARTPEC-7
- ARTPEC-6
- Ambarella CV25
- Ambarella S5L
- Ambarella S3L
- Ambarella S2L

### Version history

This API was introduced in API version earlier than 3.0.
