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

# Install xpack ARM GCC toolchain globally
RUN npm install --global @xpack-dev-tools/arm-none-eabi-gcc

# Manually extract and link the binaries
RUN PACKAGE_DIR=$(npm list -g @xpack-dev-tools/arm-none-eabi-gcc | grep -oP '(?<=\/)@xpack-dev-tools\/arm-none-eabi-gcc@[^\s]+') && \
    if [ -z "$PACKAGE_DIR" ]; then echo "Package not found"; exit 1; fi && \
    FULL_PATH="/usr/local/lib/node_modules/$PACKAGE_DIR" && \
    mkdir -p /opt/arm-gcc && \
    cp -r $FULL_PATH/* /opt/arm-gcc/ && \
    ln -s /opt/arm-gcc/bin/* /usr/local/bin/

# Verify installation
RUN arm-none-eabi-gcc --version

# Set the working directory inside the container
WORKDIR /workspaces/stm32-devops-template

# Default command for the container
CMD ["bash"]