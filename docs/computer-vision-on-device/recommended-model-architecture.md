---
layout: page
parent: Computer vision on device
title: Recommended model architecture
nav_order: 7
---

# Recommended model architecture

When working on image classification, object detection, segmentation, or any other problem, it is important to understand the components of a model architecture: the backbone and the head. The backbone extracts features from the input image, while the head is responsible for the specific task.

When choosing a model architecture, consider the DLPU (Deep Learning Processing Unit) you plan to deploy on. The backbone should be optimized for that DLPU, while the head can be switched based on the task at hand.

For example, the `SSD MobileNet` architecture has a MobileNet backbone and an SSD head. You can use the same backbone with a different head for a different task.

## General considerations

The models suggested in this page are the best trade off between easy of use, accuracy and speed on an Axis device. They are meant to allow real time inference on the edge, if your application requires higher accuracy than what the standard versions of the model can provide, the best approach is to change the hyperparameters of these same models to scale them up. For example, you can increase the input size of the model, or the number of layers in the backbone. This will allow you to get a more accurate model, but it will also increase the inference time. Be aware that changing some of the hyperparameters of the model will require you to retrain the model from scratch.

## Artpec-7

The Artpec-7 DLPU is based on the EdgeTPU, so you can use any model architecture supported by the EdgeTPU. Check out the [EdgeTPU image classification models](https://coral.ai/models/image-classification/) and [EdgeTPU object detection models](https://coral.ai/models/object-detection/) for a list of supported models. We recommend using `MobileNet v2` as the backbone.

## Artpec-8

For Artpec-8, we recommend models with `MobileNet v2` as the backbone. For object detection, you can consider using `SSD MobileNet v2` or `SSDLite MobileDet`. These models can be trained using the [TensorFlow Object Detection API](https://github.com/tensorflow/models/blob/master/research/object_detection/g3doc/tf1.md). `Resnet-18` is a better backbone than `MobileNet v2` for Artpec-8, it is a good idea to switch to it if you aim for better performance, however there are no ready to use configuration for that backbone in the TensorFlow Object Detection API.
Please note that TensorFlow 1.15 should be used, as TensorFlow 2's default quantization is not optimized for Artpec-8.

Another option for Artpec-8 is to use Yolov5. Refer to the [yolov5-on-Artpec-8](https://github.com/AxisCommunications/axis-model-zoo/blob/main/docs/yolov5-on-artpec8.md) tutorial for more information on training Yolov5 for Artpec-8.

## CV25

For CV25, we also recommend models with MobileNet v2 as the backbone. `SSD MobileNet v2` and `SSDLite MobileDet` are good choices for object detection. These models can be trained using the [TensorFlow Object Detection API](https://github.com/tensorflow/models/blob/master/research/object_detection/g3doc/tf1.md).

The Ambarella toolchain documentation provides additional examples and guides on training and optimizing models for the CV25 DLPU.

To learn how to optimize your model for the DLPUs, continue reading the [Optimization tips](./optimization-tips) page.
