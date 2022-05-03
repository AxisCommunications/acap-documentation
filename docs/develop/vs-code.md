---
layout: page
parent: Develop applications
title: Set up Visual Studio Code
nav_order: 7
---

# Setting up Visual Studio Code

Visual Studio Code provides access to containerized development tools, without the need for you to install them natively on your development computer.

To start developing ACAPs using Visual Studio Code:

1. Install the **Remote - Containers** extension available in the **Extensions Marketplace** in **Visual Studio Code**.
2. Create a subfolder called `.devcontainer` in the top directory of the source code project you are working on.
3. In `.devcontainer`, create a Dockerfile with the following content:

   ```dockerfile
   FROM axisecp/acap-native-sdk:1.0-armv7hf-ubuntu20.04
   CMD /bin/bash
   ```

   Also create a `devcontainer.json` file in `.devcontainer` with the following content:

   ```json
   {
       "name": "ACAP Native SDK",
       "build": {
           "dockerfile": "Dockerfile"
       }
   }
   ```

4. Press **Ctrl+Shift+P** and type in `Remote-Containers: Reopen in Container`.

The application restarts and is now attached to a container with the SDK and your code. This way, you can interactively edit your source code just as if the tools had been installed natively, including using all the debugging and support features in Visual Studio Code.

You can install different versions of the SDK in separate containers. When you open your source code folder, Visual Studio Code identifies the SDK version defined in the Dockerfile.

The ACAP Native SDK container includes all the SDK tools, Git and some other useful things. But you can add more tools to the Dockerfile and the devcontainer.json configuration. See [Microsofts tutorials on how to use Development Containers](https://code.visualstudio.com/docs/remote/containers) for more information on what this way of working can offer.
