---
layout: default
title: Computer Vision SDK
parent: API
nav_order: 2
---

# Computer Vision SDK APIs

## Introduction
The ACAP Computer Vision SDK contains well-known, open source packages that have been tuned for the Axis platforms and in some cases tailored to provide additional functionality for Axis devices. The main focus for the SDK is computer vision applications, and Python computer vision applications in particular. But the foundation in the container-based ACAP framework along with the high-level APIs makes for an incredibly versatile platform that lends itself to almost any concept.

On this page, the Axis-specific additions are detailed, along with a general inventory of the open source packages in the SDK. Application examples using the SDK can be found in the [acap-computer-vision-sdk-examples repository](https://github.com/AxisCommunications/acap-computer-vision-sdk-examples). The Dockerfile that builds the SDK can be found in the [acap-computer-vision-sdk repository](https://github.com/AxisCommunications/acap-computer-vision-sdk), which can be useful when for example, rebuilding OpenCV with other modules or to get an idea of how the supplied packages are crosscompiled.

## Compatibility
The table below shows ACAP Computer Vision SDK and firmware version compatibility.

SDK version | Available from firmware version
----------- | -------------------------------
1.0 | 10.7
1.1 | 10.9

## SDK index
**[SDK packages with AXIS-specific functionality](#sdk-packages-with-axis-specific-functionality)**
* [Video capture API](#video-capture-api): [OpenCV with VDO](#opencv-with-vdo)
* [Machine learning API](#machine-learning-api): [TensorFlow Serving](#tensorflow-serving-inference-client)

**[SDK package index](#sdk-package-index)**
* [Python 3](#python-3)
* [Python 3 packages](#python-3-packages)
  * [pip](#pip)
  * [NumPy](#numpy)
  * [SciPy](#scipy)
  * [OpenCV](#opencv)
  * [PyTesseract](#pytesseract)
  * [TensorFlow Serving inference client](#tensorflow-serving-inference-client)
* [Tesseract](#tesseract)
* [OpenBLAS](#openblas)
* [OpenCV with VDO](#opencv-with-vdo)
* [OpenCL](#opencl)

---

## SDK packages with AXIS-specific functionality
### Video capture API
The [OpenCV package](#opencv-with-vdo) has been extended with functionality for capturing camera images and accessing and modifying video stream and image properties. This was done by making the [OpenCV VideoCapture-class](https://docs.opencv.org/4.5.3/d8/dfe/classcv_1_1VideoCapture.html) interface with the [AXIS VDO library](4.1/api/vdostream/html/index.html), which allows for treating the Axis camera like any other OpenCV-compatible camera.

The parts of the OpenCV API that are affected by this addition are documented below.

#### The VideoCapture object
Instantiation of a VideoCapture object takes one argument: the channel index, for example, `0`:

```python
import cv2
cap = cv2.VideoCapture(0)
```

Reading an image frame from the VideoCapture is done through the common OpenCV API:

```python
retval, frame = cap.read()
```


#### VideoCapture properties
Configuration of the video stream can be done through the properties of the VideoCapture object. This includes setting resolution, image format, frames per second and such options. While similar results can be achieved by for example, resizing the retrieved image manually in OpenCV, the configuration done with VideoCapture properties is performed using hardware acceleration, which can be significantly faster and frees up CPU time.

The properties are set or get using the standard VideoCapture `get(PROPERTY_ID)` and `set(PROPERTY_ID, VALUE)` functions. `PROPERTY_ID` is an OpenCV int enum and `VALUE` is a double. Some properties are only readable, while others are writable or both readable and writable. Additionally, certain properties can only be set before the video stream is _initialized_, which is after the first image has been retrieved. Below is an example on how to set a property on a video stream, in this case the frame rate:

```python
cap.set(cv2.CAP_PROP_FPS, 10)
```

Similarily, a property can be get by doing:

```python
fps = cap.get(cv2.CAP_PROP_FPS)
```

The native image format, which is also the default image format, is `NV12`. This format is hardware accelerated, along with the monochrome `Y800` format. The widely used RGB format is available through the `RGB3` FourCC, but this format is not hardware accelerated and as such, using it may limit the maximum frame rate and slow down the application. Video stream image format, in this case RGB, can be configured through setting the `CAP_PROP_FOURCC` property with the corresponding FourCC as:

```python
cap.set(cv2.CAP_PROP_FOURCC, cv2.VideoWriter_fourcc(*'RGB3'))
```


The table below describes properties that are either Axis-specific or common OpenCV properties that have been integrated with the VDO backend.


 |  Property ID                         | Operations | Default value    |  Description                                   |  Notes                                                           |
 |:-------------------------------------|:-----------|:-----------------|:-----------------------------------------------|:-----------------------------------------------------------------|
 | `CAP_PROP_FPS`                       | get, set   | 0                | Frames per second                              | Set before initialization.                                       |
 | `CAP_PROP_FOURCC`                    | get, set   | 842094158 (NV12) | The FourCC of the stream image format          | Value given as a FourCC. Set before initialization.              |
 | `CAP_PROP_CHANNEL`                   | get, set   | 0                | The index of the camera channel                | Set before initialization.                                       |
 | `CAP_PROP_FRAME_WIDTH`               | get, set   | N/A              | The image width                                | Set before initialization.                                       |
 | `CAP_PROP_FRAME_HEIGHT`              | get, set   | N/A              | The image height                               | Set before initialization.                                       |
 | `CAP_PROP_UNIMATRIX_MAX_BUFFERS`     | get, set   | 3                | Maximum buffers in-flight                      |                                                                  |
 | `CAP_PROP_ZOOM`                      | get        | N/A              | The camera zoom factor                         |                                                                  |
 | `CAP_PROP_FOCUS`                     | get        | N/A              | The focus dioptre                              |                                                                  |
 | `CAP_PROP_GAIN`                      | get        | N/A              | Gain in milli-dB                               |                                                                  |
 | `CAP_PROP_EXPOSURE`                  | get        | N/A              | The exposure in µs                             |                                                                  |
 | `CAP_PROP_POS_MSEC`                  | get        | N/A              | The last retrieved frame's internal timestamp  |                                                                  |
 | `CAP_PROP_POS_FRAMES`                | get        | N/A              | The number of frames retrieved                 |                                                                  |
 | `CAP_PROP_UNIMATRIX_FNUMBER`         | get        | N/A              | f-number                                       |                                                                  |
 | `CAP_PROP_UNIMATRIX_ROTATION`        | set        | N/A              | The image rotation                             | Accepted values are: 0, 90, 180, 270. Set before initialization. |
 | `CAP_PROP_UNIMATRIX_EXPOSURE_MODE`   | set        | N/A              | The exposure mode                              | One of `CAP_UNIMATRIX_EXPOSURE_MODE_AUTO` (automatic exposure), `CAP_UNIMATRIX_EXPOSURE_MODE_HOLD` (hold current exposure), `CAP_PROP_UNIMATRIX_MAX_EXPOSURE_us` (limit max automatic exposure time as µs)                                      |
 | `CAP_PROP_UNIMATRIX_TONEMAPPING`     | get, set   | 50               | The tonemapping                                | A value in the [0, 100] range                                    |
 | `CAP_PROP_UNIMATRIX_TEMPORAL_FILTER` | get, set   | 50               | The amount of temporal noise filtering         | A value in the [0, 100] range                                    |
 | `CAP_PROP_UNIMATRIX_FD`              | get        | N/A              | Buffer file descriptor                         |                                                                  |
 | `CAP_PROP_UNIMATRIX_FD_OFFSET`       | get        | N/A              | Buffer offset                                  |                                                                  |
 | `CAP_PROP_UNIMATRIX_FD_CAPACITY`     | get        | 3110400          | Buffer capacity                                |                                                                  |


[^1]:

#### VideoCapture requirements

For all of the Axis extensions of OpenCV to work properly, some requirements on the container must be satisfied. This is primarily in the form of file mounts and environment variables that need to be configured. A docker-compose file is a convenient way of making sure that the app container is always run with the correct setup. Such a setup, for a fictitious app called `my-opencv-app`, is shown below, where the `ipc`, `environment`, `volumes` and `devices` keys and their corresponding values are needed for a fully functional OpenCV app:

**docker-compose.yml**
```yml
version: '3.3'

services:
  my-opencv-app:
    image: my-opencv-image:latest
    ipc: "host"
    environment:
      - DBUS_SYSTEM_BUS_ADDRESS=unix:path=/var/run/dbus/system_bus_socket
    volumes:
      - /usr/lib/libvdostream.so.1:/usr/lib/libvdostream.so.1
      - /var/run/dbus/system_bus_socket:/var/run/dbus/system_bus_socket:rw
      - /var/run/statuscache:/var/run/statuscache:rw
    devices:
      - /dev/datacache0:/dev/datacache0:rw
```

---

### Machine learning API
The ACAP Computer Vision SDK provides a flexible way of allowing machine learning inference in the form of TensorFlow Serving and a [TensorFlow Serving client](#tensorflow-serving-inference-client). TensorFlow Serving allows for making inference calls over gRPC to another container running a model server. This has several benefits, including exposing a common API for inference and having a single process handle all apps' DLPU communication.

Through Dockerhub and the ACAP Computer Vision SDK, both a model server for _larod_ and a Python client are available. The model server, called `larod-inference-server`, is available on Dockerhub under the [axisecp/larod-inference-server](https://hub.docker.com/r/axisecp/larod-inference-server) repository. The Python client is available in the ACAP Computer Vision SDK under `/axis/python-tfserving` and imported in Python as `InferenceClient`, which is available in the `tf_proto_utils` module. The client exposes a single `infer(inputs, model_name)` function that enables easy inference using the model server.

A minimal, but complete, example of how a Python client and a model server running on the same camera could be set up is shown in the [minimal-ml-example](https://github.com/AxisCommunications/acap-computer-vision-sdk-examples/tree/master/minimal-ml-inference) on Github which is a part of the [ACAP Computer Vision SDK examples](https://github.com/AxisCommunications/acap-computer-vision-sdk-examples).

## SDK package index
The ACAP Computer Vision SDK includes many packages, some of which are specific to for example, Python or only available in a certain SDK container. Below is an overview of the packages supplied in the SDK along with their location within the SDK container, and a brief description.

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

#### [TensorFlow Serving inference client](https://github.com/AxisCommunications/acap-computer-vision-sdk/blob/master/sdk/tfserving/tf_proto_utils.py)
`/axis/python-tfserving`: A Python client for the TensorFlow Serving framework. Detailed in the [Machine Learning API section](#machine-learning-api).

---

### [OpenCV](https://github.com/opencv/opencv) with VDO
`/axis/opencv`: A computer vision library with functionality that covers many different fields within computer vision. The VDO integration allows accessing the camera's video streams through the OpenCV VideoCapture class, as detailed in [Video Capture API](#video-capture-api). Compiled with OpenBLAS.

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
`/axis/tfproto`: TensorFlow and TensorFlow Serving protobuf files for compiling applications that use their API. An example of how they are used is available in the [object-detector-cpp](https://github.com/AxisCommunications/acap-computer-vision-sdk-examples/tree/master/object-detector-cpp) example.
Only available on the -devel image as the proto files are only during compilation.
