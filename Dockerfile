# Use a lightweight base image
FROM ubuntu:20.04

# Set environment variables for non-interactive installation
ENV DEBIAN_FRONTEND=noninteractive

# Update and install required packages
RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
    software-properties-common \
    wget \
    git \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

    # Download and install arm-none-eabi-gcc
RUN wget -qO- https://developer.arm.com/-/media/Files/downloads/gnu-rm/12.2.rel1/gcc-arm-none-eabi-12.2.rel1-x86_64-linux.tar.bz2 \
    | tar -xj -C /opt/ \
    && ln -s /opt/gcc-arm-none-eabi-12.2.rel1/bin/* /usr/local/bin/

    # Verify installation
RUN arm-none-eabi-gcc --version

# Set the working directory inside the container
WORKDIR /workspaces/stm32-devops-template

# Default command for the container
CMD ["bash"]