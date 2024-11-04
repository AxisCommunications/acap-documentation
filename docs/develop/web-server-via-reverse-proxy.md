---
layout: page
parent: Develop ACAP applications
title: Web server via Reverse Proxy
nav_order: 5
---

# Web server via Reverse Proxy

[Reverse Proxy configuration](https://httpd.apache.org/docs/2.4/howto/reverse_proxy.html) provides a flexible way for an ACAP application to expose an external API through the Apache Server in AXIS OS system and internally route the requests to a small Web Server running in the ACAP application.

Web Server via Reverse Proxy is a technique that can be used for exposing many types of network APIs and can e.g. cover same CGI use cases as axHttp API from ACAP version 3 SDK.

The Web Server running in the ACAP application can also be exposed directly to the network by allowing external access to the port in the network configuration for the device. There are some disadvantages with exposing Web Server directly to the network such as non standard ports and no reuse of authentication, TLS and other features that comes with Apache Server.

## Examples

- [Native Web Server](https://github.com/AxisCommunications/acap-native-sdk-examples/tree/main/web-server)
  - An example of an ACAP application using [Monkey web server](https://github.com/monkey/monkey) which exposes an external API with Reverse Proxy configuration in Apache Server.
