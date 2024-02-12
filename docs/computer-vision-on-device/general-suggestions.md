---
layout: page
parent: Computer vision on device
title: General suggestions
nav_order: 6
---

# General Suggestions

## CPU vs DLPU

Using the DLPU will speed up the inference time, but it comes at an extra development cost, as you need to adapt the model to the DLPU. Depending on the DLPU available in your device and the model you are trying to use, the conversion overhead can vary. If you need to run inference infrequently, and your CPU is not under other loads, and you don't have latency constraints, it might be easier to just use the CPU.

## Accuracy of your application

The overall accuracy of your application is determined by three factors: the model architecture, the quality of data used in training, and the training pipeline. When running a model on an edge device like an Axis camera, you are constrained in the type of model architecture you can use. Therefore, it becomes even more important to have a good dataset and a good training pipeline. It is crucial to have a training dataset that contains images similar to the ones your application will encounter. Adding Axis camera frames to the dataset is the best way to improve the performance of your model, on the other hand, having only camera frame from the same static scene in your dataset will reduce the generalizability of your model. Having a good training pipeline will also improve the quality of the final model. Adding features like data augmentation, custom loss function, regularization, early stopping, and learning rate decay will help you get a better model.

## Picking the model

If you are not an expert, we recommend using only the models provided in the [recommended model architecture](./recommended-model-architecture) section of this documentation or in the [Axis Model Zoo](https://github.com/AxisCommunications/axis-model-zoo). Picking a model from another repository might require a lot of work to adapt it to the DLPU, and it is probably not worth the effort, unless you know what you are doing.

## Use standard architectures

When running Deep Learning models on the edge, you should not expect the same flexibility and performance as when you run your model on the cloud on a GPU. Therefore, you should not expect to be able to run the latest cutting-edge model architecture on your Axis device. Visual transformers and deformable convolutions are not recommended at the moment. Stick to more traditional architectures like `ResNet`, `MobileNet`, and `EfficientNet`. These architectures are well supported by the DLPU and are known to perform well on edge devices.

Continue reading about [recommended model architecture](./recommended-model-architecture).
