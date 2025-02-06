---
layout: page
parent: Develop ACAP applications
title: Proxy
nav_order: 11
redirect_to: https://developer.axis.com/acap/develop/proxy
---

# Proxy

## Proxy in build time

The ACAP Native SDK build environment use Docker and if the build machine
is positioned inside a network with proxy, the Docker toolchain needs to be
configured.

### Docker daemon proxy

To enable pull of ACAP Native SDK images from Docker Hub in a network with
proxy, the Docker daemon needs to be configured. For instructions see
<https://docs.docker.com/engine/daemon/proxy>.

### Docker build environment

The build instruction of ACAP applications is defined in the `Dockerfile` and if
the application build tries to connect to external resources such as installing
Ubuntu packages via `apt` or downloading files via `curl` in a network with
proxy, the Docker CLI needs to be configured. For instructions see
<https://docs.docker.com/engine/cli/proxy>.

## Proxy in runtime

To make an ACAP application use a proxy during runtime, it's possible to
configure a global device proxy. Global device proxy settings act as global
environment variables in AXIS OS. There are three types of global device
proxies that can be configured; `HTTP_PROXY`, `HTTPS_PROXY`, and `NO_PROXY`.

### Configure global device proxy

Global device proxy can be set via either:

- The VAPIX
  [Network Settings API](https://developer.axis.com/vapix/network-video/network-settings-api#setglobalproxyconfiguration-1).
- The network page at `http://<AXIS_DEVICE_IP>/index.html#system/network` and
  section `Global proxies`.

### How are ACAP applications affected?

ACAP applications can be affected by global device proxy if they use the curl
API or in any other way are able to pick up proxy from environment variables.
