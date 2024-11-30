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
    tar \
    gzip \
    cmake \
    ninja-build \
    gcc \
    g++ \
    python3 \
    python3-pip \
    libstdc++-arm-none-eabi-newlib \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

# Download and install xpack ARM GCC toolchain
RUN ARCH=$(uname -m) && \
    case "$ARCH" in \
      x86_64) DOWNLOAD_URL="https://github.com/xpack-dev-tools/arm-none-eabi-gcc-xpack/releases/download/v13.3.1-1.1/xpack-arm-none-eabi-gcc-13.3.1-1.1-linux-x64.tar.gz";; \
      aarch64) DOWNLOAD_URL="https://github.com/xpack-dev-tools/arm-none-eabi-gcc-xpack/releases/download/v13.3.1-1.1/xpack-arm-none-eabi-gcc-13.3.1-1.1-linux-arm64.tar.gz";; \
      arm*) DOWNLOAD_URL="https://github.com/xpack-dev-tools/arm-none-eabi-gcc-xpack/releases/download/v13.3.1-1.1/xpack-arm-none-eabi-gcc-13.3.1-1.1-linux-arm.tar.gz";; \
      *) echo "Unsupported architecture: $ARCH" && exit 1;; \
    esac && \
    wget -O gcc.tar.gz "$DOWNLOAD_URL" && \
    mkdir -p /opt/arm-gcc && \
    tar -xzf gcc.tar.gz -C /opt/arm-gcc --strip-components=1 && \
    rm gcc.tar.gz && \
    ln -s /opt/arm-gcc/bin/* /usr/local/bin/

# Verify installation
RUN arm-none-eabi-gcc --version

# Set the working directory inside the container
WORKDIR /workspaces/stm32-devops-template

# Default command for the container
CMD ["bash"]