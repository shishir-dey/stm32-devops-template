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
    curl \
    npm \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

# Install xpack ARM GCC toolchain
RUN npm install --global @xpack-dev-tools/arm-none-eabi-gcc

# Find and symlink the ARM GCC binaries
RUN GCC_PATH=$(find /root/.local/xPacks/@xpack-dev-tools/arm-none-eabi-gcc -name "bin" -type d | head -n 1) && \
    if [ -z "$GCC_PATH" ]; then echo "ARM GCC toolchain not found"; exit 1; fi && \
    ln -s $GCC_PATH/* /usr/local/bin/

# Verify installation
RUN arm-none-eabi-gcc --version

# Set the working directory inside the container
WORKDIR /workspaces/stm32-devops-template

# Default command for the container
CMD ["bash"]