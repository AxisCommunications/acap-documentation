---
layout: page
parent: Develop applications
title: Include third party lib
nav_order: 4
---

## Include third party libraries

### ACAP Native SDK
Below is a generic guide on how to build and include a third-party library in your application using the ACAP Native SDK.

The third-party library build is taken care of by the Docker file. So while building the third-party library, update and install all necessary build tools needed to build a specific third-party library. Refer to one of the examples in [utility-libraries](https://github.com/AxisCommunications/acap-native-sdk-examples/tree/master/utility-libraries) that show how supporting build tools are installed, and how third-party library compilation for **armv7hf** is done using the Docker file.

#### Overview of Docker commands used to build the third-party library and generate an ACAP application

Docker command to install supporting build tools:
```Dockerfile
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
         <ubuntu-package>
```
Cloning of the source code to build the third-party library must be made to a specific work directory in the Docker container.

Docker command to switch to the third-party library build directory:
```Dockerfile
WORKDIR /opt/build
```

Now clone the source code to `/opt/build` directory, from which the third-party library is generated:
```Dockerfile
RUN git clone < Third-party source code github path>
```

Go to the cloned directory:
```Dockerfile
WORKDIR /opt/build/<cloned directory>
```

Before building a third-party library:
* Source the cross-compilation environment setup file.
* Configure output build directory path for custom library build using [--prefix]
* Include cross compiler flags if any.
* Run `make`
* Below is one of the examples with respect to curl:

```Dockerfile
#  lib generate
# - Source the SDK environment script to get links to cross compiler through
# - CONFIGURE_FLAGS environment variable
WORKDIR /opt/build/curl
RUN . /opt/axis/acapsdk/environment-setup* && \
    autoreconf -fi && \
    ./configure --prefix=${PWD}/build ${CONFIGURE_FLAGS} --without-ssl && \
    make && \
    make install
```

Once the build is successful copy the generated library directory to the `/opt/app/lib` folder.
```Dockerfile
# Copy the library to application folder
ARG BUILDDIR=/opt/build/curl
COPY ./app /opt/app/
WORKDIR /opt/app
RUN mkdir lib && cp -r ${BUILDDIR}/build lib
```

`/opt/app/lib` folder contains cross-compiled shared library files that will be included in the ACAP.

In the application Makefile, enter the custom library header file and library path, and link the library.
```bash
LDLIBS += -Llib/
CFLAGS += -Ilib/include
SHLIB_DIR = ./lib
LDFLAGS = -L$(SHLIB_DIR) -Wl,--no-as-needed,-rpath,'$$ORIGIN/lib'
SHLIBS += -lm -l[lib](linking-third-party-lib)
```
#### Importance of setting **RPATH**
The **RPATH** setting is to change the library search path so that one executable or library can link the desired dependent libraries during run-time.

> Set **RPATH** to the directory where shared libraries are located, with the
> help of **$ORIGIN**.  This will tell the linker to search and include
> libraries under the specified library path, usually used to override the
> default library paths.


Once all of the above configurations are made you are ready to build and install the application. See [Build, install and run with custom application image](build-install-run#build-install-and-run-with-custom-application-image).

#### Troubleshooting
Normally, the Configure file is available when building a custom library for a
specific architecture.  If the Configure file is not available, then create an
output build directory using Makefile, and copy generated lib files to the
output library directory as shown in the reference below.

```bash
mkdir -p build
mkdir -p build/include
cp *.h build/include
cp [lib.so] build/
```

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

With the emulation functionality available, third party packages can be installed. An example of this is shown in the Dockerfile below, in which an armv7hf image with some packages from the ACAP Computer Vision SDK and the third party Python library `requests` is built. Some packages require more of the build environment, and in those cases, creating a new environment with the correct toolchains and `-devel` tagged packages and copying the output to the runtime container is recommended.

```Dockerfile
FROM axisecp/acap-computer-vision-sdk:latest-armv7hf AS cv-sdk
FROM arm32v7/ubuntu:20.04

# Add the CV SDK packages
COPY --from=cv-sdk /axis/opencv /
COPY --from=cv-sdk /axis/python /
COPY --from=cv-sdk /axis/python-numpy /
COPY --from=cv-sdk /axis/openblas /

# Add the python package requests
RUN pip3 install requests

# Add your application files
COPY app /app
WORKDIR /app
CMD ["python3", "some_analytics_script.py"]
```

Python packages are not commonly distributed as binaries for the arm platforms, so packages downloaded onto runtime images from, for example, [PyPI](https://pypi.org/) will likely have to be compiled from source. An updated list of the ACAP Computer Vision SDK packages, that are precompiled with OpenBLAS (when applicable) and optimized for the AXIS platforms, can be found in [the ACAP Computer Vision SDK repository](https://github.com/AxisCommunications/acap-computer-vision-sdk#contents).
