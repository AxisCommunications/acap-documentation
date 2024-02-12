---
layout: page
parent: Computer vision on device
title: Test your model
nav_order: 9
---

# Test your model

## Introduction

Before developing an application to run your model on a device, it's important to test the model to ensure it meets your requirements and is suitable for your use case. Testing the model allows you to evaluate its performance and make any necessary adjustments before proceeding with application development.

## Test your model on the device

To test your model on the device, you can use the `larod-client` tool. Follow these steps:

1. Connect to your device using ssh.
2. Run the following command:

```bash
larod-client -a
```

This command will provide you with a list of all the interfaces that larod can use to run your model.

```bash
larod-client -a
2023-12-05T10:56:58.019 Connecting to larod...
2023-12-05T10:56:58.036 Connected
2023-12-05T10:56:58.036 Devices:
___________________________________________
 Name                             Instance
‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 cpu-tflite                       0
 axis-ace-proc                    0
 cpu-proc                         0
 axis-a8-dlpu-tflite              0
 axis-a8-dlpu-native              0
 axis-a8-dlpu-proc                0
 axis-a8-gpu-proc                 0
___________________________________________

```

To test the performance of your model on the DLPU, you can use the `larod-client` command with the following options:

```bash
larod-client -g <model_file> -c axis-a8-dlpu-tflite -R 100 -w 5 -i ''
```

This command runs the specified model on the Artpec-8 DLPU and performs 100 inferences. The `-i ''` option indicates that no input is required, as you are only testing the speed.

Before running this command, make sure that the model is loaded on the device.

When you run the command, the output will be displayed in the console. It will show the connection status, model loading status, setup of input tensors, and the execution time for the job. Here is an example of the output:

```bash
larod-client -g ./mobilenet_v2_1.0_224_quant.tflite
 -c axis-a8-dlpu-tflite -R 100 -i ''
2023-12-05T15:47:31.748 Connecting to larod...
2023-12-05T15:47:31.765 Connected
2023-12-05T15:47:57.308 Model mobilenet_v2_1.0_224_quant.tflite loaded
2023-12-05T15:47:57.308 Setting up randomly generated input tensors using random seed 1701787677
2023-12-05T15:47:57.321 Running job for 100 round(s)...
2023-12-05T15:47:57.881 Output written to:
2023-12-05T15:47:57.882 1701787677.out0
2023-12-05T15:47:57.882 Mean execution time for job: 5.60 ms
```

The output provides information about the connection status, model loading status, setup of input tensors, and the mean execution time for the job.

The output of the inference is saved in a file, such as `1701787677.out0` in the example above. Since the input was random, the output is not relevant. However, the mean execution time for the 100 inferences is shown, which in this case is 5.60 ms.

## Input and output with the model

If you are interested in providing an input and obtaining an output from the model, you can use the `-i` option to specify the input file for the model, and the `-o` option to specify the output file.

To specify the input and output files when using the larod-client command, use the following syntax:

```bash
larod-client -g <model_file> -c axis-a8-dlpu-tflite -R 1 -o <output_file> -i <input_file>
```

The `<input_file>` should be a binary file containing the input for the model.
There is also a major difference in the input format between Artpec-7/8 and CV25, for Artpect the input is expected to be rgb-interleaved, while for CV25 the input is expected to be rgb-planar.

You can use the following Python code snippets to convert an image to the required binary format for an Artpec device:

```python
import numpy as np
import cv2

img = cv2.imread('image.jpg')
img = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
img.tofile('input.bin')
```

For CV25, the input is expected to be rgb-planar, so you need to transpose the image before saving it to the binary file:

```python
import numpy as np
import cv2

img = cv2.imread('image.jpg')
img = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
img = img.transpose(2, 0, 1)
img.tofile('input.bin')
```

Running the above command will produce the same results as before, but the output will be saved in the file specified by the `-o` option. The output file will be a binary file containing the output of the model. You will need to parse it according to your model output format.

Here is an example of running the command with input and output files specified:

```bash
larod-client -g ./mobilenet_v2_1.0_224_quant.tflite -c axis-a8-dlpu-tflite -R 1 -i ./input.bin -o output.bin
2023-12-05T15:58:34.521 Connecting to larod...
2023-12-05T15:58:34.538 Connected
2023-12-05T15:58:35.492 Model mobilenet_v2_1.0_224_quant.tflite loaded
2023-12-05T15:58:35.492 Running job for 100 round(s)...
2023-12-05T15:58:36.049 Output written to:
2023-12-05T15:58:36.049 output.bin
2023-12-05T15:58:36.049 Mean execution time for job: 5.57 ms
```

## Retrieve device logs

If you encounter any errors with the commands mentioned above, you can retrieve the device logs by using the following command:

```bash
journalctl -u larod
```

This command will provide you with the logs from the larod service, which can help you identify and understand the issue you are experiencing. Common messages you may encounter indicate that certain layers in your network are not supported. To ensure proper functionality, ensure that your network only includes supported layers. For more information, refer to the [supported-frameworks](./supported-frameworks.md) section.
