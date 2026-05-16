# STM32 DevOps Template

Repository for showcasing DevOps practices within microcontroller projects.

## Overview

The STM32 DevOps Template is a comprehensive embedded systems project that demonstrates modern DevOps practices applied to microcontroller development. This template showcases efficient data structures, automated testing, and continuous integration/deployment pipelines specifically designed for STM32 microcontrollers.

## Build Status
[![CMake](https://github.com/shishir-dey/stm32-devops-template/actions/workflows/cmake.yml/badge.svg)](https://github.com/shishir-dey/stm32-devops-template/actions/workflows/cmake.yml)
[![Generate Sphinx documentation](https://github.com/shishir-dey/stm32-devops-template/actions/workflows/sphinx.yml/badge.svg)](https://github.com/shishir-dey/stm32-devops-template/actions/workflows/sphinx.yml)
[![Pages Build & Deployment](https://github.com/shishir-dey/stm32-devops-template/actions/workflows/pages/pages-build-deployment/badge.svg)](https://github.com/shishir-dey/stm32-devops-template/actions/workflows/pages/pages-build-deployment)

## Quick Start

### Building for Host (Testing)
```bash
mkdir cmake-host-build-debug && cd cmake-host-build-debug
cmake -DHOST=ON ..
make
ctest
```

### Building for STM32 Target
```bash
mkdir cmake-target-build-debug && cd cmake-target-build-debug
cmake -DCMAKE_TOOLCHAIN_FILE=../cmake/arm-none-eabi-gcc.cmake ..
make
```

### Generating Documentation
```bash
cd docs
pip install -r requirements.txt
make html
```

## Project Structure

```
stm32-devops-template/
├── src/                    # Source code
│   ├── data/              # Data structure implementations
│   ├── main.c             # Main application
│   └── autogen/           # Generated files (startup, linker)
├── test/                   # Unity unit tests
├── lib/Unity/             # Unity testing framework
├── docs/                   # Sphinx documentation
├── cmake/                  # CMake toolchain and modules
└── .github/workflows/      # CI/CD pipelines
```
