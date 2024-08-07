---
layout: default
title: Computer Vision SDK APIs
parent: API
nav_order: 2
---

# Computer Vision SDK APIs

## Introduction

The ACAP Computer Vision SDK contains well-known, open source packages that have been tuned for the Axis platforms and in some cases tailored to provide additional functionality for Axis devices. The main focus for the SDK is computer vision applications, and Python computer vision applications in particular. But the foundation in the container-based ACAP framework along with the high-level APIs makes for an incredibly versatile platform that lends itself to almost any concept.

On this page, the Axis-specific additions are detailed, along with a general inventory of the open source packages in the SDK. Application examples using the SDK can be found in the [acap-computer-vision-sdk-examples repository](https://github.com/AxisCommunications/acap-computer-vision-sdk-examples). The Dockerfile that builds the SDK can be found in the [acap-computer-vision-sdk repository](https://github.com/AxisCommunications/acap-computer-vision-sdk), which can be useful when for example, rebuilding OpenCV with other modules or to get an idea of how the supplied packages are cross-compiled.

## Compatibility

To find compatibility between ACAP Computer Vision SDK and AXIS OS version,
refer to [Find the right SDK for software compatibility](../axis-devices-and-compatibility/#find-the-right-sdk-for-software-compatibility).

## SDK index

**[SDK packages with AXIS-specific functionality](#sdk-packages-with-axis-specific-functionality)**

- [ACAP Runtime APIs](#acap-runtime-apis)
- [Video capture API](#video-capture-api)
- [Machine learning API](#machine-learning-api): [TensorFlow Serving](#tensorflow-serving-inference-client)
- [BETA - Parameter API](#beta---parameter-api)

**[SDK package index](#sdk-package-index)**

<!-- no toc -->
- [Python 3](#python-3)
- [Python 3 packages](#python-3-packages)
  - [pip](#pip)
  - [NumPy](#numpy)
  - [SciPy](#scipy)
  - [OpenCV](#opencv)
  - [PyTesseract](#pytesseract)
  - [TensorFlow Serving inference client](#tensorflow-serving-inference-client)
- [Tesseract](#tesseract)
- [OpenBLAS](#openblas)
- [OpenCL](#opencl)
- [TensorFlow protobuf files](#tensorflow-protobuf-files)

---

## SDK packages with AXIS-specific functionality

### ACAP Runtime APIs

The ACAP Runtime service provides the following APIs:

- [Video capture API](#video-capture-api): Enables capture of images from a camera
- [Machine learning API](#machine-learning-api): Tensorflow Serving for inference service
- [BETA - Parameter API](#beta---parameter-api): Axis parameter service

ACAP Runtime acts as a server that exposes the above APIs as gRPC APIs by using [gRPC](https://grpc.io) and a [UNIX domain socket (UDS)](https://grpc.github.io/grpc/cpp/md_doc_naming.html) for access. The access is restricted to applications in the device that belongs to the `sdk` user group.

The recommended way to use ACAP Runtime is to install Docker ACAP or Docker Compose ACAP on the device, and then load and run the ACAP Runtime Docker image. Detailed instructions for installation can be found [here](https://github.com/AxisCommunications/acap-runtime/?tab=readme-ov-file#containerized-version).

### Video capture API

The Video capture API is one of the services of ACAP Runtime.

The ACAP Computer Vision SDK offers a mechanism for capturing frames using the ACAP Runtime. By sending a gRPC request to the ACAP runtime, users can establish a video stream and retrieve frames.

The Python client is accessible within the ACAP Computer Vision SDK at /axis/python-vdoproto and is imported into Python as VideoCaptureClient, located within the vdo_proto_utils module. This client exposes the get_frame function, facilitating frame retrieval and parsing.

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

For the video capture client to work, it is required that the ACAP runtime is installed and running, either as an ACAP application or as a Docker container.
The application and the ACAP runtime need to share a socket file to allow the gRPC communication.
In the case of the containerized ACAP runtime, it means there should be a volume mounted between the application and the containerized ACAP runtime.
An example can be found in the [opencv-qr-decoder-python](https://github.com/AxisCommunications/acap-computer-vision-sdk-examples-staging/blob/main/opencv-qr-decoder-python/docker-compose.yml)

---

### Machine learning API

The Machine learning API is one of the services of ACAP Runtime.

The ACAP Computer Vision SDK provides a flexible way of allowing machine learning inference in the form of TensorFlow Serving and a [TensorFlow Serving client](#tensorflow-serving-inference-client). TensorFlow Serving allows for making inference calls over gRPC to another container, the inference server, and a model server. This has several benefits, including exposing a common API for inference and having a single process handle all apps' DLPU communication.

The Python client is available in the ACAP Computer Vision SDK under `/axis/python-tfserving` and imported in Python as `InferenceClient`, which is available in the `tf_proto_utils` module. The client exposes a single `infer(inputs, model_name)` function that enables an easy inference from the main application that will also be connected to the model server.

#### Code Examples

- [minimal-ml-inference](https://github.com/AxisCommunications/acap-computer-vision-sdk-examples/tree/main/minimal-ml-inference) - A minimal, but complete, example of how a Python client and a model server running on the same camera.

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

## SDK package index

The ACAP Computer Vision SDK includes many packages, some of which are specific to for example, Python or only available in a certain SDK container. Below is an overview of the packages supplied in the SDK along with their location within the SDK container as well as a brief description.

---

### [Python 3](https://docs.python.org/3.8/)

`/axis/python`: A Python 3.8 installation to allow easy prototyping and development of applications.

---

### Python 3 packages

#### [pip](https://pip.pypa.io/en/stable/getting-started/)

A Python package manager that allows easy installation of third party Python packages. Included in the Python 3 package.

#### [NumPy](https://github.com/numpy/numpy)

`/axis/python-numpy`: A Python package for scientific computing. Compiled with OpenBLAS.

#### [SciPy](https://github.com/scipy/scipy)

`/axis/python-numpy`: A Python package with various mathematics, science and engineering capabilities. Compiled with OpenBLAS.

#### [OpenCV](https://github.com/opencv/opencv)

A Python OpenCV package is included in the `/axis/opencv` package as a module called `cv2`. Compiled with OpenBLAS.

#### [PyTesseract](https://github.com/madmaze/pytesseract)

`/axis/python-pytesseract`: A Python interface to the Tesseract Optical Character Recognition engine.

#### [TensorFlow Serving inference client](https://github.com/AxisCommunications/acap-computer-vision-sdk/blob/main/sdk/tfserving/tf_proto_utils.py)

`/axis/python-tfserving`: A Python client for the TensorFlow Serving framework. Detailed in the [Machine learning API section](#machine-learning-api).

---

### [Video capture client](https://github.com/AxisCommunications/acap-computer-vision-sdk/blob/main/sdk/vdoproto/vdo_proto_utils.py)

`/axis/python-vdoproto`: A Python video capture client for collecting frames using gRPC calls to the ACAP runtime.

---

### [OpenCV](https://github.com/opencv/opencv)

`/axis/opencv`: A computer vision library with functionality that covers many different fields within computer vision.

---

### [Tesseract](https://github.com/tesseract-ocr/tesseract)

`/axis/tesseract`: An OCR engine developed by Google. Requires model from for example, [tessdata](https://github.com/tesseract-ocr/tessdata) to be downloaded and have its location specified in the application.

---

### [OpenBLAS](https://github.com/xianyi/OpenBLAS)

`/axis/openblas`: A library with optimized linear algebra operations which can accelerate many applications. Applications that use libraries that have been compiled with OpenBLAS should also include OpenBLAS to ensure compatibility.

---

### [OpenCL](https://www.khronos.org/registry/OpenCL/sdk/1.2/docs/man/xhtml/)

`/axis/opencl`: A general purpose parallel programming language.
Only available on the `-devel` image as the runtime files are mounted from the camera.

---

### TensorFlow protobuf files

`/axis/tfproto`: TensorFlow and TensorFlow Serving protobuf files for compiling applications that use their API. An example of how they are used is available in the [object-detector-cpp](https://github.com/AxisCommunications/acap-computer-vision-sdk-examples/tree/main/object-detector-cpp) example.
Only available on the -devel image as the proto files are only during compilation.
