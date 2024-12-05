---
layout: page
parent: Develop ACAP applications
title: Global device proxy
nav_order: 10
---

# Global device proxy

Global device proxy settings act as global environment variables on the Axis device. There are three
types of global device proxies that can be configured; `HTTP_PROXY`, `HTTPS_PROXY`, and `NO_PROXY`.

## Configure global device proxy

Global device proxy can be set via either:

- The VAPIX
  [Network Settings API](https://developer.axis.com/vapix/network-video/network-settings-api#setglobalproxyconfiguration-1).
- The network page at `http://<AXIS_DEVICE_IP>/index.html#system/network` and section
  `Global proxies`.

## How are ACAP applications affected?

ACAP applications can be affected by global device proxy if they use the curl API or in any other
way are able to pick up proxy from environment variables.
