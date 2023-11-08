---
layout: acap_sdk_version_3
parent: ACAP SDK version 3
title: What's new in ACAP SDK
nav_order: 7
---
# What's new in ACAP SDK

- [What's new in release 3.5](#whats-new-in-release-35)
- [What's new in release 3.4.2](#whats-new-in-release-342)
- [What's new in release 3.4.0](#whats-new-in-release-340)
- [What's new in release 3.3.0](#whats-new-in-release-330)
- [What's new in release 3.2.0](#whats-new-in-release-320)
- [What's new in release 3.1.0](#whats-new-in-release-310)
- [What's new in release 3.0.1](#whats-new-in-release-301)

## What's new in release 3.5

New features

- ARTPEC-8 support
- Manifest schema 1.3 and architecture

Library or tool updates

- glibc updated to version 2.33

Deprecated APIs

- Media Capture (libcapture.so) is removed from this SDK version.

## What's new in release 3.4.2

Library or tool updates

- Changed the GCC directory search option format from `-L dir` to `-Ldir` in the SDK compiler variables in ACAP build tools. See [GCC documentation](https://gcc.gnu.org/onlinedocs/gcc/Directory-Options.html#Directory-Options) for more information.
- Added a symbolic link that points python to python3. In ACAP SDK 3.4 and earlier, python3 is installed but some programs and scripts rely on the python command.

## What's new in release 3.4.0

New features

- All application defines and configurations fully supported in tools for conversion to manifest based ACAP application.
- Build command updated to support reproducible builds. See [Reproducible builds](../develop-applications/reproducible-builds) for more information.

Library or tool updates

- glibc 2.32

New APIs

- **larod 2.0** - Handles TFLite when using firmware version 10.6 and later.

## What's new in release 3.3.0

New features

- **Support for `manifest.json`** - used for application defines and configurations such as app name and version. `manifest.json` is a JSON based manifest file enabling schema validation for error handling. The SDK includes a tool for converting `package.conf` to a manifest file. We recommend using the manifest now to future proof your application. See [Manifest file](../develop-applications/application-project-structure#manifest-file) for more information.

New APIs

- **larod 2.0** - New version of machine learning API with support for hardware
   accelerated image pre-processing operations crop, scale and color-space
   conversion.

## What's new in release 3.2.0

New features

- A toggle that controls loading of signed ACAP applications, see [Accept or deny unsigned ACAP applications](../services-for-partners/accept-or-deny-unsigned-acap-applications).

Library or tool updates

- gcc updated to version 9.3.

Other changes

- From this release on, the ACAP SDK is available on [DockerHub](https://hub.docker.com/r/axisecp/acap-toolchain) only.

Deprecated APIs

- Capture is removed from SDK and firmware after the next firmware LTS. Use [Video capture API](../api/video-capture-api) instead.

## What's new in release 3.1.0

Library or tool updates

- gcc updated to version 9.2.

Other changes

- From this release, the ACAP toolchain and ACAP API are available as container images on [DockerHub](https://hub.docker.com/r/axisecp/acap-toolchain).

New APIs

- [Machine learning API](../api/machine-learning-api)

## What's new in release 3.0.1

Library or tool updates

- gcc updated to version 8.3.

Other changes

- ACAP SDK not available for the mips architecture from this version.

New APIs

- [Overlay API](../api/overlay-api)
- [Open standard APIs](../api/open-standsard-apis)
- [Video capture API](../api/video-capture-api)
