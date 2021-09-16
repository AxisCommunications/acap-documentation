---
layout: default
title: API
nav_order: 5
has_children: true
---

# API

The SDK provides the following APIs:

**Video and audio APIs**

* [Video capture API](#video-capture-api): VdoStream
* [Machine learning API](#machine-learning-api): Larod
* [Overlay API](#overlay-api): Axoverlay

**Application support APIs**
* [Event API](#event-api): Axevent
* [License API](#license-api): LicenseKey

Go to the [ACAP API documentation](api-doc/3.4/main/html/acap4_api.html) for detailed functional descriptions and examples of the APIs.

## API versions
The table below shows API and firmware version compatibility.

API version | Available from firmware version
----------- | -------------------------------
API 3.0 | 9.70
API 3.1 | 9.80
API 3.2 | 10.2
API 3.3 | 10.5
API 3.4 | 10.6

## Video capture API
Go to the [ACAP API documentation](api-doc/3.4/api/vdostream/html/index.html) for detailed functional descriptions and examples of this API.

The VdoStream API provides:
* video and image stream
* video and image capture
* video and image configuration

### Compatibility
The API supports products with the following chips:
* ARTPEC-7
* ARTPEC-6
* Ambarella S5L
* Ambarella S5
* Ambarella S3L
* Ambarella S2L

### Version history
The VdoStream API was introduced in API version 3.0.

### Code Examples
#### Capture video stream
This code example on [GitHub](https://github.com/AxisCommunications/acap3-examples/tree/master/vdostream) starts a vdo stream and then illustrates how to continuously capture frames from the vdo service, access the received buffer contents as well as the frame metadata.

#### libvdo and larod combined
This code example on [GitHub](https://github.com/AxisCommunications/acap3-examples/tree/master/vdo-larod) loads an image classification model to larod and then uses vdo to fetch frames of size WIDTH x HEIGHT in yuv format which are converted to interleaved rgb format and then sent to larod for inference on MODEL.

## Machine learning API
Go to the [ACAP API documentation](api-doc/3.4/api/larod/html/index.html) for detailed functional descriptions and examples of this API.

liblarod lets you communicate with the Larod machine learning service, and use its features. The Machine learning API can be used for deep learning applications.

### Compatibility
The API supports products with the following chips:
* ARTPEC-7
* Ambarella S5L

For products with a DLPU (Deep Learning Processing Unit), inference runs on the DLPU otherwise it runs on the CPU.

### Version history

Larod API version | ACAP API version | What’s new
----------------- | ---------------- | ----------
1.0 | 3.1 | Larod API introduced
2.0 | 3.3 | Preprocessing functionality, Handles TFLite when using firmware version 10.6 and later.

> We recommend using Larod version 2.0. However you can still use Larod version 1.0. To use Larod 1.0, define LAROD_API_VERSION_1 in your application, see Backward compatibility in Introduction to larod for app developers for more information.

### Code Examples
#### Extract and analyze output
This code example on [GitHub](https://github.com/AxisCommunications/acap3-examples/tree/master/larod) connects to larod and loads a model, runs inference on it and then finally deletes the loaded model from larod.

#### libvdo and larod combined
This code example on [GitHub](https://github.com/AxisCommunications/acap3-examples/tree/master/vdo-larod) loads an image classification model to larod and then uses vdo to fetch frames of size WIDTH x HEIGHT in yuv format which are converted to interleaved rgb format and then sent to larod for inference on MODEL.

## Overlay API
Go to the [ACAP API documentation](api-doc/3.4/api/axoverlay/html/index.html) for detailed functional descriptions and examples of this API.

The Axoverlay API is a helper library that enables an ACAP to draw overlays in selected video streams. It has built-in support for Cairo as rendering API, as well as an open backend for any other custom rendering.

### Compatibility
The API supports products with the following chips:
* ARTPEC-7
* ARTPEC-6

### Version history
The Axoverlay API was introduced in API version 3.0.

### Code Examples
#### Draw plain boxes and text
This code example on [GitHub](https://github.com/AxisCommunications/acap3-examples/tree/master/axoverlay) shows how to draw plain boxes and text as overlays in a stream with the Axoverlay API.

## Event API
Go to the [ACAP API documentation](api-doc/3.4/api/axevent/html/index.html) for detailed functional descriptions and examples of this API.

The Axevent API provides:
* an interface to the event system found in Axis products.
* applications with a mechanism for sending and receiving events.

An application can both send and receive events.

**Event types**

**Stateless (Pulse)** – An event that indicates that something has occurred. Typically used to trigger some action rule.

**Stateful (State)** – An event with an active and inactive state. Typically used in action rules like “record while active”.

**Data (Application Data)** – An event that includes data that needs to be processed by the consuming application such as transaction data, license plate or other dynamic data. A data event is normally not used to trigger generic action rules.

**Supported Namespaces**

When declaring events it is required to set a namespace. Following are the supported namespaces:

**tnsaxis** – Axis namespace to use with Axis events

**tns1** – ONVIF namespace to use with ONVIF events

### Compatibility
The API supports products with the following chips:
* ARTPEC-7
* ARTPEC-6
* Ambarella S5L
* Ambarella S5
* Ambarella S3L
* Ambarella S2L

### Version history

Event API version | ACAP API version | What’s new
----------------- | ---------------- | ----------
1.0 | ACAP 2 | Event API introduced
1.1 | 3.2 | New functions: ax_event_new2, ax_event_get_time_stamp2

> **ax_event_new** and **ax_event_get_time_stamp** functions are marked as deprecated from ACAP API version 3.2 because they use [GTimeVal](https://developer.gnome.org/glib/stable/glib-Date-and-Time-Functions.html#GTimeVal), which is deprecated in glib. Use **ax_event_new2** and **ax_event_get_time_stamp2** instead.

### Code Examples
#### Subscribe to and send event
This code example on [GitHub](https://github.com/AxisCommunications/acap3-examples/tree/master/axevent) illustrates both how to subscribe to different events and how to send an event.

## License API
Go to the [ACAP API documentation](api-doc/3.4/api/licensekey/html/index.html) for detailed functional descriptions and examples of this API.

Use the LicenseKey API to validate an application license key.

A license key is a signed file, generated for a specific device ID and application ID. The ACAP Service Portal maintains both license keys and application IDs.

### Compatibility
The API supports products with the following chips:
* ARTPEC-7
* ARTPEC-6
* Ambarella S5L
* Ambarella S5
* Ambarella S3L
* Ambarella S2L

### Version history
This API was introduced in API version earlier than 3.0.

### Code Examples
#### Status of a license key
This code example on [GitHub](https://github.com/AxisCommunications/acap3-examples/tree/master/licensekey) shows how to check the status of a license key.
