---
layout: page
parent: Computer vision on device
title: Supported frameworks
nav_order: 3
---

# Supported frameworks

All DLPUs, except for CV25, support only the [TensorFlow Lite](https://www.tensorflow.org/lite) format. CV25 uses a proprietary format, but it can be converted from TensorFlow Lite or ONNX. When using the tflite model, keep in mind that only tflite built-in int8 ops are supported to run on the DLPU `tf.lite.OpsSet.TFLITE_BUILTINS_INT8`. Custom ops or TensorFlow ops are not supported.

## Converting from TensorFlow or Keras to TensorFlow Lite

To convert a TensorFlow/Keras model to a tflite model, you can use the tflite converter. This is the most reliable way to convert a model to tflite. Here is an example code snippet on how to convert a model to tflite:

```python
import tensorflow as tf

converter = tf.lite.TFLiteConverter.from_saved_model(saved_model_dir)
converter.optimizations = [tf.lite.Optimize.DEFAULT]
converter.representative_dataset = a_representative_datagenerator
converter.target_spec.supported_ops = [tf.lite.OpsSet.TFLITE_BUILTINS_INT8]
converter.inference_input_type = tf.uint8
converter.inference_output_type = tf.uint8
tflite_quant_model = converter.convert()
```

You can find the full code example [here](https://github.com/AxisCommunications/acap-native-sdk-examples/blob/main/tensorflow-to-larod/env/convert_model.py).

## Converting from ONNX to TensorFlow Lite

All Axis DLPUs, except for CV25, do not support ONNX models. However, you can try converting an ONNX model to a tflite model using the unofficial [onnx2tf](https://github.com/PINTO0309/onnx2tf) tool. Please note that this tool is not supported by Axis, and there is no guarantee that the conversion will work or that the converted model will run on the device. Debugging may be required to make the model run on the device.

## Converting from PyTorch to TensorFlow Lite

Axis DLPUs do not support PyTorch models. However, you can export a PyTorch model to ONNX and then convert it to tflite. You can find an example [here](https://pytorch.org/tutorials/advanced/super_resolution_with_onnxruntime.html). Please note that jumping from PyTorch to ONNX to TFlite is not recommended and may require a lot of trial and error.

## Using Non-Supported Frameworks

Although PyTorch and ONNX are not supported, it is theoretically possible to run a Python script that uses PyTorch or ONNX runtime to run the model in a Docker container on the device. Please note that this is not supported by Axis, and there is no guarantee that it will work smoothly. Keep in mind that the model will only run on the CPU and will not take advantage of the DLPU to accelerate the inference.

Continue reading about [Quantization](./quantization) to learn more about correctly quantizing the model.
