---
layout: page
title: Integration with other systems
nav_order: 11
---

# Integration with other systems

A network camera is, more often than not, part of a solution that aims towards solving a specific use case. You might wish to send commands to the camera, or the camera is controlling another device via one of its I/O ports, or data generated on the camera should be sent over the network to an endpoint that aggregates data from multiple devices? In any of these circumstances we need to create the integration between the camera and its counterpart. And easy integration is key for any successful project that involved more than one part.

This chapter aims to describe various integrations, hopefully covering relevant parts of your solution.

## Integration with cloud

Some use cases will require an integration with the cloud. You might be building a cloud application that reads data streams, and wish to send data generated on the camera to this application? Or you might wish to send an image from the camera when an event is triggered? For those, or other, situation we can provide you with sample examples, serving as building blocks in your solution. We currently have repositories on GitHub, tailored towards the following cloud vendors.

- [Amazon Web Services (AWS)](https://github.com/AxisCommunications/acap-integration-examples-aws) - Integration between Axis devices and Amazon Web Services (AWS)
- [Microsoft Azure](https://github.com/AxisCommunications/acap-integration-examples-azure) - Integration between Axis devices and Microsoft Azure
- [Google Cloud Platform (GCP)](https://github.com/AxisCommunications/acap-integration-examples-gcp) - Integration between Axis devices and Google Cloud Platform (GCP)

If you find yourself wishing there was another example more relevant to your use case, please don't hesitate to start a discussion or open a new issue in the relevant GitHub repository.
