---
layout: page
title: Cloud integrations
nav_order: 8
---

# Cloud integrations

A network device is, more often than not, part of a solution that aims towards solving a specific use case. You might wish to send commands to the device, or the device to control another device via one of its I/O ports, or you want data generated on the device to be sent over the network to an endpoint that aggregates data from multiple devices? In any of these circumstances you need to create the integration between the device and its counterpart. Easy integration is key for any successful project that involves more than one part.

Some use cases require an integration with the cloud. You might be building a cloud application that reads data streams, and wish to send data generated on the device to this application? Or you might wish to send an image from the camera when an event is triggered? For the above and for other use cases we can provide you with examples, serving as building blocks in your solution. We currently have examples on GitHub for the following cloud vendors:

- Amazon Web Services (AWS)
  - [Sending images from a camera to AWS S3](https://github.com/AxisCommunications/acap-integration-examples-aws/tree/main/images-to-aws-s3)
  - [Sending telemetry from a device to AWS IoT Core](https://github.com/AxisCommunications/acap-integration-examples-aws/tree/main/telemetry-to-aws-iot-core)
- Google Cloud Platform (GCP)
  - [Sending images from a camera to Google Cloud Storage](https://github.com/AxisCommunications/acap-integration-examples-gcp/tree/main/images-to-google-cloud-storage)
- Microsoft Azure
  - [Sending images from a camera to Azure storage account](https://github.com/AxisCommunications/acap-integration-examples-azure/tree/main/images-to-azure-storage-account)
  - [Sending telemetry from a device to Azure IoT Edge](https://github.com/AxisCommunications/acap-integration-examples-azure/tree/main/telemetry-to-azure-iot-edge)
  - [Sending telemetry from a device to Azure IoT Hub](https://github.com/AxisCommunications/acap-integration-examples-azure/tree/main/telemetry-to-azure-iot-hub)

If you require other examples more relevant to your use case, please don't hesitate to start a discussion or open a new issue in the relevant GitHub repository.
