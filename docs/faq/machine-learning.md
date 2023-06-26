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

- [What backbone/architecture do you recommend for TPU/ARTPEC-8/CV25?](#what-backbonearchitecture-do-you-recommend-for-tpuartpec-8cv25)
- [My model is developed for ARTPEC-7 (TPU). How do I run it on ARTPEC-8?](#my-model-is-developed-for-artpec-7-tpu-how-do-i-run-it-on-artpec-8)
- [What is the training process for the respective accelerator?](#what-is-the-training-process-for-the-respective-accelerator)
- [What is a Deep Learning Processing Unit (DLPU) and how does it relate to the Central Processing Unit (CPU)?](#what-is-a-deep-learning-processing-unit-dlpu-and-how-does-it-relate-to-the-central-processing-unit-cpu)
- [Can a Deep Learning Processing Unit (DLPU) run multiple models?](#can-a-deep-learning-processing-unit-dlpu-run-multiple-models)

## What backbone/architecture do you recommend for TPU/ARTPEC-8/CV25?

The [FAQ in the ACAP Computer Vision example repository](https://github.com/AxisCommunications/acap-computer-vision-sdk-examples/discussions/112) explains a lot when it comes to model support for different Axis architectures. Additionally, we have the [Axis Model Zoo repository](https://github.com/AxisCommunications/axis-model-zoo) that contains a collection of different models compatible with Axis cameras and some performance measures (accuracy and speed).

## My model is developed for ARTPEC-7 (TPU). How do I run it on ARTPEC-8?

A few aspects of this question are answered in [ACAP Computer Vision SDK examples #112](https://github.com/AxisCommunications/acap-computer-vision-sdk-examples/discussions/112), but in general, a model that works on ARTPEC-7 can also work on ARTPEC-8. The difference is not about the model's architecture but an optimization stage called *quantization*. Make sure to use *quantization by tensor* on ARTPEC-8, since it is the most optimal solution on that platform.

You can also find relevant information on model conversion, model quantization and image formats in the [ACAP Native SDK examples](https://github.com/AxisCommunications/acap-native-sdk-examples) repository, specifically for [ARTPEC-7](https://github.com/AxisCommunications/acap-native-sdk-examples/tree/main/tensorflow-to-larod), [ARTPEC-8](https://github.com/AxisCommunications/acap-native-sdk-examples/tree/main/tensorflow-to-larod-artpec8) and [CV25](https://github.com/AxisCommunications/acap-native-sdk-examples/tree/main/tensorflow-to-larod-cv25).

## What is the training process for the respective accelerator?

The [ACAP Native SDK examples](https://github.com/AxisCommunications/acap-native-sdk-examples) repository contains examples on the training process for [ARTPEC-7](https://github.com/AxisCommunications/acap-native-sdk-examples/tree/main/tensorflow-to-larod), [ARTPEC-8](https://github.com/AxisCommunications/acap-native-sdk-examples/tree/main/tensorflow-to-larod-artpec8) and [CV25](https://github.com/AxisCommunications/acap-native-sdk-examples/tree/main/tensorflow-to-larod-cv25).

## What is a Deep Learning Processing Unit (DLPU) and how does it relate to the Central Processing Unit (CPU)?

The DLPU is a separate component in the Axis device specialized to be performant for deep learning algorithms, where the more general CPU is responsible for executing operative system instructions.

## Can a Deep Learning Processing Unit (DLPU) run multiple models?

Yes, Axis devices are capable of running multiple models concurrently but not in parallel. With multiple models the DLPU will have to switch between inferences, and the load will not be divided equally if the models aren't similar in size and complexity. As a guideline you should only run models that benefit you in your use case, e.g. stop [AXIS Object Analytics](https://www.axis.com/products/axis-object-analytics) if it's not contributing to your use case.
