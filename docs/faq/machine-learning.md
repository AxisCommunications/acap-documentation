---
layout: page
parent: FAQ
title: Machine learning
nav_order: 1
---

<!-- omit in toc -->
# Machine learning

<!-- omit in toc -->
## Table of contents

- [How do I get started with machine learning (ML) on Axis devices?](#how-do-i-get-started-with-machine-learning-ml-on-axis-devices)
- [What models are recommended for my SoC?](#what-models-are-recommended-for-my-soc)
- [What exact layers are supported?](#what-exact-layers-are-supported)
- [Is PyTorch or other formats supported?](#is-pytorch-or-other-formats-supported)
- [What is the training process for the respective accelerators?](#what-is-the-training-process-for-the-respective-accelerators)
- [What is a Deep Learning Processing Unit (DLPU) and how does it relate to the Central Processing Unit (CPU)?](#what-is-a-deep-learning-processing-unit-dlpu-and-how-does-it-relate-to-the-central-processing-unit-cpu)
- [Can a Deep Learning Processing Unit (DLPU) run multiple models?](#can-a-deep-learning-processing-unit-dlpu-run-multiple-models)
- [My model is developed for ARTPEC-7 (TPU). How do I run it on ARTPEC-8?](#my-model-is-developed-for-artpec-7-tpu-how-do-i-run-it-on-artpec-8)
- [How do I test and debug my model on my device?](#how-do-i-test-and-debug-my-model-on-my-device)
- [Why do I loose accuracy after quantization?](#why-do-i-loose-accuracy-after-quantization)

## How do I get started with machine learning (ML) on Axis devices?

It is possible to work with machine learning (ML) on various Axis devices. For an example on how to
implement machine learning on Axis devices, see the [computer vision][get-started-1]
documentation.

[get-started-1]: https://developer.axis.com/computer-vision

## What models are recommended for my SoC?

The [recommended model architecture][models-for-soc-1] gives guidance on what machine learning
models to use for different SoCs like ARTPEC-7, ARTPEC-8 and CV25. Additionally, the
[Axis Model Zoo][models-for-soc-2] repository contains a collection of different models compatible
with Axis cameras and some performance measures (accuracy and speed).

[models-for-soc-1]: https://developer.axis.com/computer-vision/computer-vision-on-device/recommended-model-architecture
[models-for-soc-2]: https://github.com/AxisCommunications/axis-model-zoo

## What exact layers are supported?

For recommendations about model layers, go to [general suggestions][sup-layers-1], specifically the
paragraph [use simple layers][sup-layers-2]. Tips for choosing layers that work for a specific
accelerator can be found in the [optimization tips][sup-layers-3] section.

To verify that the layers do not yield any errors, follow the instructions in
[test your model][sup-layers-4].

[sup-layers-1]: https://developer.axis.com/computer-vision/computer-vision-on-device/general-suggestions
[sup-layers-2]: https://developer.axis.com/computer-vision/computer-vision-on-device/general-suggestions#use-simple-layers
[sup-layers-3]: https://developer.axis.com/computer-vision/computer-vision-on-device/optimization-tips
[sup-layers-4]: https://developer.axis.com/computer-vision/computer-vision-on-device/test-your-model

## Is PyTorch or other formats supported?

No, only Tensorflow Lite is supported. See [supported frameworks][other-formats-1] for more
information and guides on how to convert other formats to Tensorflow Lite.

[other-formats-1]: https://developer.axis.com/computer-vision/computer-vision-on-device/supported-frameworks

## What is the training process for the respective accelerators?

In [ACAP Native SDK examples][train-proc-1], see the examples named **tensorflow-to-larod**.

[train-proc-1]: https://github.com/AxisCommunications/acap-native-sdk-examples

## What is a Deep Learning Processing Unit (DLPU) and how does it relate to the Central Processing Unit (CPU)?

The DLPU is designed to accelerate the execution of a model, making inference significantly faster
compared to the CPU. See [Axis Deep Learning Processing Unit (DLPU)][dlpu-1] for more information.

[dlpu-1]: https://developer.axis.com/computer-vision/computer-vision-on-device/axis-dlpu

## Can a Deep Learning Processing Unit (DLPU) run multiple models?

Yes, Axis devices are capable of running multiple models concurrently but not in parallel. With
multiple models the DLPU will have to switch between inferences, and the load will not be divided
equally if the models aren't similar in size and complexity. As a guideline, only run models that
benefits the intended use case, e.g. stop [AXIS Object Analytics][mult-models-1] if it is not
contributing to the intended use case.

[mult-models-1]: https://www.axis.com/products/axis-object-analytics

## My model is developed for ARTPEC-7 (TPU). How do I run it on ARTPEC-8?

In general, a model that works on ARTPEC-7 can also work on ARTPEC-8. The difference is not about
the model's architecture but an optimization stage called *quantization*. See
[quantization for each DLPU][model-conv-1] and
[Deep Learning Processing Unit (DLPU) model conversion][model-conv-2] for more information.

Relevant information on model conversion, model quantization and image formats can be found in the
[ACAP Native SDK examples][model-conv-3] repository, specifically for [ARTPEC-7][model-conv-4],
[ARTPEC-8][model-conv-5] and [CV25][model-conv-6].

[model-conv-1]: https://developer.axis.com/computer-vision/computer-vision-on-device/quantization#quantization-for-each-dlpu
[model-conv-2]: https://developer.axis.com/computer-vision/computer-vision-on-device/dlpu-model-conversion
[model-conv-3]: https://github.com/AxisCommunications/acap-native-sdk-examples
[model-conv-4]: https://github.com/AxisCommunications/acap-native-sdk-examples/tree/main/tensorflow-to-larod
[model-conv-5]: https://github.com/AxisCommunications/acap-native-sdk-examples/tree/main/tensorflow-to-larod-artpec8
[model-conv-6]: https://github.com/AxisCommunications/acap-native-sdk-examples/tree/main/tensorflow-to-larod-cv25

## How do I test and debug my model on my device?

Go to [test your model][test-model-1] for a detailed guide on how to test and debug a model on a
device.

[test-model-1]: https://developer.axis.com/computer-vision/computer-vision-on-device/test-your-model

## Why do I loose accuracy after quantization?

That is unfortunately normal and difficult to avoid. See the [quantization][quant-1] section
for more information.

[quant-1]: https://developer.axis.com/computer-vision/computer-vision-on-device/quantization
