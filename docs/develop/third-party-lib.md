---
layout: page
parent: Develop applications
title: Include third party lib
nav_order: 3
---

## Include third party libraries

### ACAP Native SDK
This section will be added shortly.

### ACAP Computer Vision SDK
You can add third party packages to an image based on the ACAP Computer Vision SDK in three main ways:

**Supplied packages** - Many common packages are supplied in the ACAP Computer Vision SDK. These have been compiled and tuned for the platform and in some cases, had additions that give them additional functionality, such as capturing video directly from an AXIS camera in the case of the *OpenCV with VDO* package. These packages are available in the ACAP Computer Vision SDK under the `/axis` directory and are currently installed during the `docker build` process simply through copying the package path to the root of the target in the Dockerfile, e.g., in the case of OpenCV: `COPY --from=cv-sdk /axis/opencv /`. In this case, `cv-sdk` is defined as seen in the `Dockerfile` in the [Emulated installation](#emulated-installation) section, which also shows a complete example of adding packages from the ACAP Computer Vision SDK to an application.

**Cross-compiled** - Cross-compiled packages are compiled in a container with one instruction set and built for being run in a container with another instruction set. Cross-compilation commonly requires custom configuration. See [Cross-compilation](#cross-compilation) below for more information.

**Emulated** - The emulated way of installing packages involves running an emulated container and executing installation commands as usual, for example, using apt-get for OS packages and pip for Python packages. Emulated installations are often slower, due to being emulated, but also easier to set up as the platform's regular toolchain can be used. See [Emulated installation](#emulated-installation) below for more information.


#### Cross-compilation
A common setup is compiling on a desktop with x86_64 for use on armhf, as used by ARTPEC-7-equipped devices. Guidance can be found in the [ACAP Computer Vision SDK examples](https://github.com/AxisCommunications/acap-computer-vision-sdk-examples). The toolchain used (for example, `crossbuild-essential-armhf`) to cross-compile the application for the target platform is present in the `devel`-tagged corresponding ACAP Computer Vision SDK image. Flags that have been used for compilation of the ACAP Computer Vision SDK packages are available under the `$ARCH_CFLAGS` variable in the `devel`-tagged image.


#### Emulated installation
For Python packages, cross-compiling can be difficult, and being able to use a package manager directly inside the runtime container can be convenient. Luckily, the Python package manager `pip` and other standard utilities such as `apt-get` can be run directly in the runtime container. However, as this container likely has a non-native instruction set, the commands need to be emulated, which requires some setup. One way to allow emulation of `RUN` commands in non-native containers is through the use of [QEMU](https://qemu-project.gitlab.io/qemu/about/index.html). Installation of the necessary components, on which more information can be found in the [multiarch/qemu-user-static](https://github.com/multiarch/qemu-user-static) repository, can conveniently be done by executing:

```bash
docker run --rm --privileged multiarch/qemu-user-static --reset -p yes
```

Once this is finished, emulated RUN commands can be executed. The emulation functionality can be tested by building a Dockerfile that performs a `RUN` command in a non-native container, such as the minimal one shown below:
```Dockerfile
FROM arm32v7/ubuntu:20.04
RUN echo "'Hello World!' -an $(uname -m) program"
```

If your QEMU installation succeeded, this should output `'Hello World!' -an armv7l program`.

With the emulation functionality available, third party packages can be installed. An example of this is shown in the Dockerfile below, in which an armv7hf image with some packages from the ACAP Computer Vision SDK and the third party Python library `pandas` is built.

```Dockerfile
FROM axisecp/acap-computer-vision-sdk:latest-armv7hf AS cv-sdk
FROM arm32v7/ubuntu:20.04

# Add the CV SDK packages
COPY --from=cv-sdk /axis/opencv /
COPY --from=cv-sdk /axis/python /
COPY --from=cv-sdk /axis/python-numpy /
COPY --from=cv-sdk /axis/openblas /

# Add the python package pandas
RUN pip3 install pandas

# Add your application files
COPY app /app
WORKDIR /app
CMD ["python3", "some_analytics_script.py"]
```

Python packages are not commonly distributed as binaries for the arm platforms, so packages downloaded onto runtime images from, for example, [PyPI](https://pypi.org/) will likely have to be compiled from source. An updated list of the ACAP Computer Vision SDK packages, that are precompiled with OpenBLAS (when applicable) and optimized for the AXIS platforms, can be found in [the ACAP Computer Vision SDK repository](https://github.com/AxisCommunications/acap-computer-vision-sdk#contents).

