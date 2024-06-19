---
layout: page
parent: Computer vision on device
title: Optimization tips
nav_order: 8
---

# Optimization tips

This document provides optimization tips for each DLPU (Deep Learning Processing Unit).
It is meant for a more advanced audience, that want to obtain the best performance possible from their model investing more time in the optimization process. If you are not an expert, we recommend using only the models provided in the [recommended model architecture](./recommended-model-architecture) section of this documentation or in the [Axis Model Zoo](https://github.com/AxisCommunications/axis-model-zoo).

## ARTPEC-7

The ARTPEC-7 DLPU has a dedicated memory for the DLPU. To maximize the DLPU's performance, it is recommended to use lightweight models that can fit in this memory, such as SSD MobileNet v2 300x300.

When converting your model to EdgeTPU using `edgetpu-converter`, you may receive warnings about instructions that cannot be executed by the TPU. It is important to avoid using these instructions in your model.
Both per-channel and per-tensor quantization offer similar performance, but per-channel quantization is recommended for better accuracy.
For more details on how to optimize your model for ARTPEC-7 DLPU, refer to the [EdgeTPU documentation](https://coral.ai/docs/).

## ARTPEC-8

The ARTPEC-8 DLPU performs well with models of any size, as long as they fit in the device's memory. This allows for better performance with larger models compared to ARTPEC-7. Here are some additional optimizations to enhance DLPU performance:

- **Use per-tensor quantization.**
- Prefer regular convolutions over depth-wise convolutions, which means that architecture like RegNet-18 are more efficient than MobileNet.
- Optimal kernel size is 3x3.
- Use stride 2 whenever possible as it is natively supported by the convolution engine. For other cases, consider using pooling.
- Ensure the number of layers per convolution block is a multiple of 6.
- Applying ReLU as the activation function after a convolution will result in a faster fused layer.
- Sparsification can improve the performance of the model.

## CV25

For CV25, model quantization and optimizations are mainly performed by the compiler. It is recommended to refer to the documentation provided with the Ambarella SDK for more information.

One important consideration is to have a model with an input size that is a multiple of 32. Otherwise, padding will be required for the input, making the conversion process slightly more complex, and the model less efficient.

Continue reading the [Test Your Model](./test-your-model) page to learn how to test your model on the DLPU.
