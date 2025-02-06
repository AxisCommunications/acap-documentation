---
layout: acap_sdk_version_3
parent: Get started
grand_parent: ACAP SDK version 3
title: Find out which SDK to use
nav_order: 3
redirect_to: https://developer.axis.com/acap/acap-sdk-version-3/get-started/find-out-which-sdk-to-use
---
# Find out which SDK to use

Different products have different architectures depending on the chip used in the product. Consequently different SDKs are required to ensure that the ACAP application is compatible with the product. Currently, there are two different SDKs - one for products with `armv7hf` architecture, and one for products with `aarch64` architecture.

Choosing which SDK to use depends on the starting point of your development:

**I already have a specific product that I want to develop an ACAP application for** – Which SDK to use depends on the architecture of the specific product. To find out which architecture your product has, see [Check device properties](./set-up-the-device#check-device-properties).

**I want to develop an ACAP application for a specific product that I don't have access to yet** – Find out which chip a specific product has in [Product interface guide](https://www.axis.com/developer-community/acap#product-interface-guide) (requires login to Developer Community).

**I don't have a specific product, or I'm not sure which architecture to use.** – If you're not sure, use `armv7hf`, which supports most products.

> **Note**
> ACAP supports the chips listed in the [Product interface guide](https://www.axis.com/developer-community/acap#product-interface-guide).
