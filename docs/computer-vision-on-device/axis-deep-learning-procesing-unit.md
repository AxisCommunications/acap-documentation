---
layout: page
parent: Computer vision on device
title: Axis deep learning processing unit
nav_order: 2
---

# Axis Deep Learning Processing Unit (DLPU)

Some Axis devices are equipped with a Deep Learning Processing Unit (DLPU). The DLPU is designed to accelerate the execution of your model, making inference significantly faster compared to the CPU.
The speed-up you achieve using the DLPU may vary and depends on how optimized your model is for the DLPU.

## Axis devices with DLPU

To determine if a device is equipped with a DLPU, you can use the [Axis product selector](https://www.axis.com/support/tools/product-selector/shared/%5B%7B%22index%22%3A%5B4%2C1%5D%2C%22value%22%3A%22DLPU%22%7D%5D) and filter the results to show only devices with a DLPU.
It is important to note that not all devices have the same DLPU.
To identify the DLPU of your Axis device, you can check the System on Chip name (SoC) of your device.
There are currently 3 different families of device that are using a DLPU:

- Artpec-7
- Artpec 8
- CV25

## DLPU characteristics

Different DLPUs perform best with different models and may require different conversion or quantization processes.
Each DLPU will be discussed individually in the following sections.
Here is a brief overview of the characteristics of these DLPUs:

| SoC      | Speed  | Supported model format     | Quantization    | Ease of usage |
| -------- | ------ | -------------------------  | ------------    | ------------- |
| CPU      |  🐢   | .tflite                    | Not needed      | Easy          |
| Artpec-7 |  🚲   | .tflite + edgetpu-compiler | INT8            | Easy          |
| Artpec 8 |  🚗   | .tflite                    | INT8 per-tensor | Medium        |
| CV25     |  🚗   | .tflite/.onnx + compiler   | Not needed*     | Hard          |

\* Quantization is performed by the compiler

Devices with the same SoC will have the same DLPU and perform similarly.
There may be some performance differences between products with the same SoC due to variations in hardware configurations (e.g., clock speed, memory, etc.). For example, Q1656 and P3265 have the same SoC (Artpec 8), but the Q1656 has an higher clock speed and more memory, which results in better performance.

The above table intentionally does not provide specific speed values, as the performance of the accelerators depends on the model used, and it is difficult to quantify them in absolute terms.
For more insights on DLPU performance, you can refer to the [Axis model zoo](https://github.com/AxisCommunications/axis-model-zoo), where you can find benchmarks of the different accelerators using different models.
As shown in the table above, different DLPUs require different types of quantization. More details about quantization can be found in the [Quantization](./quantization) page.

Continue reading about [supported frameworks](./supported-frameworks).
