STM32 DevOps Template
=====================

.. toctree::
   :maxdepth: 2
   :caption: Contents:

   overview
   api/index
   examples
   testing

Repository for showcasing DevOps practices within microcontroller projects.

Overview
--------

The STM32 DevOps Template is a comprehensive embedded systems project that demonstrates modern DevOps practices applied to microcontroller development. This template provides:

* **Data Structures**: Implementation of efficient queue types (regular, circular, priority) suitable for embedded systems
* **Testing Framework**: Unity-based unit testing with CI/CD integration
* **Documentation**: Sphinx + Breathe for beautiful API documentation
* **Build System**: CMake-based cross-platform build configuration
* **CI/CD Pipeline**: GitHub Actions for automated testing and documentation deployment

Features
--------

* **Queue Implementations**
  
  * Regular Queue (FIFO)
  * Circular Queue (Ring Buffer)
  * Priority Queue (Binary Heap)

* **DevOps Integration**
  
  * Automated testing with Unity framework
  * Continuous integration with GitHub Actions
  * Automated documentation generation and deployment
  * Cross-platform build support (host and target)

* **Embedded Systems Focus**
  
  * Static memory allocation (no dynamic memory)
  * STM32F407 target support
  * Optimized for resource-constrained environments
  * Comprehensive error handling

Project Structure
-----------------

.. code-block:: text

   stm32-devops-template/
   ├── src/                    # Source code
   │   ├── data/              # Data structure implementations
   │   ├── main.c             # Main application
   │   └── autogen/           # Generated files (startup, linker)
   ├── test/                   # Unit tests
   ├── lib/                    # Third-party libraries
   │   └── Unity/             # Unity testing framework
   ├── docs/                   # Documentation source
   ├── cmake/                  # CMake modules
   ├── config/                 # Project configuration
   └── .github/workflows/      # CI/CD pipelines

Quick Start
-----------

**Building for Host (Testing)**

.. code-block:: bash

   mkdir build && cd build
   cmake -DHOST=ON ..
   make
   ctest

**Building for Target (STM32F407)**

.. code-block:: bash

   mkdir build && cd build
   cmake -DCMAKE_TOOLCHAIN_FILE=../cmake/arm-none-eabi-gcc.cmake ..
   make

**Generating Documentation**

.. code-block:: bash

   cd docs
   make html

Author & License
----------------

* **Author**: Shishir Dey
* **Year**: 2025
* **License**: MIT License

Indices and tables
==================

* :ref:`genindex`
* :ref:`modindex`
* :ref:`search` 