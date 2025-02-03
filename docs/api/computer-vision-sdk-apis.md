---
layout: default
title: Computer Vision APIs
parent: API
nav_order: 2
---

# Computer Vision APIs

> **Note:**
>
> - New Axis products released on AXIS OS 12.x will not have container support.
> - [All products with existing container support](https://www.axis.com/support/tools/product-selector/shared/%5B%7B%22index%22%3A%5B10%2C0%5D%2C%22value%22%3A%22ARTPEC-8%22%7D%2C%7B%22index%22%3A%5B10%2C2%5D%2C%22value%22%3A%22Yes%22%7D%5D)
>   will be supported until end of 2031 when [AXIS OS 2026 LTS](https://help.axis.com/en-us/axis-os) reaches end of life.
> - The recommended way to build analytics, computer vision and machine learning applications on Axis devices with ACAP support,
>   is to use the ACAP Native SDK. For usage see the [acap-native-sdk-examples](https://github.com/AxisCommunications/acap-native-sdk-examples)
>   repository.
> - The ACAP Computer Vision SDK has been archived as its components have been refactored:
>   utility libraries and scripts are now available in [ACAP Runtime](https://github.com/AxisCommunications/acap-runtime).
>   For usage of the new setup, see the [examples](https://github.com/AxisCommunications/acap-computer-vision-sdk-examples)
>   repository.

<!-- omit in toc -->
## Table of Contents

- [Introduction](#introduction)
- [Compatibility](#compatibility)
- [Axis APIs](#axis-apis)
  - [Video capture API](#video-capture-api)
    - [The VideoCapture object](#the-videocapture-object)
    - [VideoCapture requirements](#videocapture-requirements)
    - [Code Examples](#code-examples)
  - [Machine learning API](#machine-learning-api)
    - [Code Examples](#code-examples-1)
  - [BETA - Parameter API](#beta---parameter-api)
    - [Code Examples](#code-examples-2)
- [Python packages](#python-packages)

## Introduction

The ACAP Computer Vision solution is an ecosystem designed to run containerized applications on Axis network devices.
It includes essential components like the [Docker ACAP](https://github.com/AxisCommunications/docker-acap), which is necessary for utilizing Docker on the device,
and the [ACAP Runtime](https://github.com/AxisCommunications/acap-runtime), a runtime service that provides access to various APIs.
The primary focus are computer vision applications, especially those developed in Python, but its versatility allows it to support a wide range of applications.

This documentation details the Axis-specific additions and provides a general overview of the Computer Vision solution.
For practical examples of applications using the Computer Vision APIs, refer to the [acap-computer-vision-sdk-examples](https://github.com/AxisCommunications/acap-computer-vision-sdk-examples) repository.

## Compatibility

To find compatibility between the ACAP Computer Vision solution and AXIS OS version,
refer to [Find the right SDK for software compatibility](../axis-devices-and-compatibility/#find-the-right-sdk-for-software-compatibility).

## Axis APIs

The ACAP Runtime service provides the Axis APIs:

- [Video capture API](#video-capture-api): Enables capture of images from a camera
- [Machine learning API](#machine-learning-api): Tensorflow Serving for inference service
- [BETA - Parameter API](#beta---parameter-api): Axis parameter service

ACAP Runtime acts as a server that exposes the above APIs as gRPC APIs by using [gRPC](https://grpc.io) and a [Unix domain socket (UDS)](https://grpc.github.io/grpc/cpp/md_doc_naming.html) for access.

When using ACAP Runtime in a Docker ACAP environment:

1. Include the ACAP Runtime server in your `docker-compose.yml` file.
2. Share a volume between the ACAP Runtime container and your application container to access the socket.

For detailed instructions on how to set up and use ACAP Runtime in your Docker ACAP project, including an example `docker-compose.yml` configuration, please refer to the official [ACAP Runtime README](https://github.com/AxisCommunications/acap-runtime?tab=readme-ov-file#usage).

Additionally, the ACAP Runtime repository provides pre-built gRPC Python wrappers for client-side use. These wrappers are available as a Docker image. The [example repository](https://github.com/AxisCommunications/acap-computer-vision-sdk-examples) demonstrates how to use these wrappers and includes the necessary setup in its build instructions.

By utilizing these wrappers, you can avoid building the gRPC client-side code for Python yourself, streamlining the process of integrating and using the ACAP Runtime APIs in your application.

---

### Video capture API

The Video capture API is one of the services of ACAP Runtime.

The ACAP Computer Vision solution offers a mechanism for capturing frames using the ACAP Runtime. By sending a gRPC request to the ACAP runtime, users can establish a video stream and retrieve frames.

The Python client is accessible within the ACAP Runtime proto image at `/build/vdo/proto_utils` and is imported into Python as `VideoCaptureClient`, located within the `vdo_proto_utils` module. This client exposes the `get_frame` function, facilitating frame retrieval and parsing.

#### The VideoCapture object

To instantiate a VideoCaptureClient object, you need to provide the ACAP runtime communication socket, along with the desired stream dimensions and framerate.
In some cases, this call could take up to two minutes, if the ACAP runtime is busy doing other tasks like loading a machine learning model on start up.

```python
from vdo_proto_utils import VideoCaptureClient
capture_client = VideoCaptureClient(socket="unix:///tmp/acap-runtime.sock", stream_width=224, stream_height=224, stream_framerate=10)
```

An image frame can be read with the following line of code

```python
frame = capture_client.get_frame()
```

#### VideoCapture requirements

For the video capture client to work, it is required that the ACAP runtime is installed and running.
The application and the ACAP runtime need to share a socket file to allow the gRPC communication.
To achieve this, a volume needs to be mounted between the application and the ACAP runtime container.

#### Code Examples

- [opencv-qr-decoder-python](https://github.com/AxisCommunications/acap-computer-vision-sdk-examples-staging/blob/main/opencv-qr-decoder-python/docker-compose.yml) - A minimal example of a QR code detector and decoder application written in Python.
- [minimal-ml-inference](https://github.com/AxisCommunications/acap-computer-vision-sdk-examples/tree/main/minimal-ml-inference) - A minimal, but complete, example of how a Python client and a model server running on the same camera.
- [object-detector-python](https://github.com/AxisCommunications/acap-computer-vision-sdk-examples/tree/main/object-detector-python) - An example written in Python that implements the following object detection scenarios:
  - Run a video streaming inference on camera.
  - Run a still image inference on camera.
- [pose-estimator-with-flask](https://github.com/AxisCommunications/acap-computer-vision-sdk-examples/tree/main/pose-estimator-with-flask) - An example written in Python that implements a pose estimator, that publishes the output using Flask.

---

### Machine learning API

The Machine learning API is one of the services of ACAP Runtime.

The ACAP Computer Vision solution provides a flexible way of allowing machine learning inference in the form of TensorFlow Serving and a TensorFlow Serving client. TensorFlow Serving allows for making inference calls over gRPC to another container, the inference server, and a model server. This has several benefits, including exposing a common API for inference and having a single process handle all apps DLPU communication.

The Python client is available in the ACAP runtime proto image under `/build/tf/proto_utils` and imported in Python as `InferenceClient`, which is available in the `tf_proto_utils` module. The client exposes a single `infer(inputs, model_name)` function that enables an easy inference from the main application that will also be connected to the model server.

#### Code Examples

- [minimal-ml-inference](https://github.com/AxisCommunications/acap-computer-vision-sdk-examples/tree/main/minimal-ml-inference) - A minimal, but complete, example of how a Python client and a model server running on the same camera.
- [object-detector-python](https://github.com/AxisCommunications/acap-computer-vision-sdk-examples/tree/main/object-detector-python) - An example written in Python that implements the following object detection scenarios:
  - Run a video streaming inference on camera.
  - Run a still image inference on camera.
- [pose-estimator-with-flask](https://github.com/AxisCommunications/acap-computer-vision-sdk-examples/tree/main/pose-estimator-with-flask) - An example written in Python that implements a pose estimator, that publishes the output using Flask.

---

### BETA - Parameter API

**This API is a [Beta version](./beta-api) and developers are encouraged to test and leave feedback.**

The Parameter API is one of the services of ACAP Runtime.

The Parameter API enables an application to read the parameters of an Axis network device. There are a lot of parameters on an Axis network device in the form of key-value pairs, and the Parameter API allows us to pass the name of the parameter as the key, which will return the value of the parameter. This API can be used to read existing parameters; it can not set any new parameters.

It is necessary to use the exact parameter name to get the expected results. The parameter list can be found using the URL `http://<ip address>/axis-cgi/param.cgi?action=list` where `<ip address>` is the IP address of your device.

Here are some example parameter names:

```text
root.Properties.Firmware.Version
root.Brand.ProdFullName
root.Brand.ProdNbr
```

#### Code Examples

- [parameter-api-python](https://github.com/AxisCommunications/acap-computer-vision-sdk-examples/tree/main/parameter-api-python) - A Python example which reads device parameters using the Parameter API.

---

## Python packages

The ACAP Computer Vision solution allows for the installation and use of Python packages that support the ACAP architecture `aarch64`. This includes, but is not limited to:

- **NumPy**: Used for handling large multi-dimensional arrays and matrices.
- **OpenCV**: Utilized for image processing, video capture, and analysis.
- **Flask**: A web framework for setting up web servers and creating RESTful APIs.

Examples demonstrating the use of these Python packages can be found in the [ACAP Computer Vision examples](https://github.com/AxisCommunications/acap-computer-vision-sdk-examples) repository.
