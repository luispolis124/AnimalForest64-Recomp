# AnimalForest64-Recomp Documentation

Welcome to the **AnimalForest64-Recomp** project documentation. This repository provides a native PC port framework for *Animal Forest* (N64) utilizing modern recompilation architecture.

## Overview
This project builds upon the established N64 recompilation ecosystem, leveraging advanced rendering and user interface libraries to bring classic Nintendo 64 titles to modern hardware natively, without traditional emulation overhead.

## Core Libraries Used
* **RT64**: Modern rendering engine providing enhanced graphical features and upscaling.
* **RmlUi**: HTML/CSS-based framework used for building custom menus and the game launcher.
* **lunasvg & FreeType**: Handles vector graphics (SVG) and font rendering for the user interface.
* **moodycamel::ConcurrentQueue**: High-performance, lock-free MPMC queues for thread synchronization.

## Compilation Guide (PC)
To compile the project natively on your PC:
1. Clone the repository recursively:
   ```bash
   git clone --recursive https://github.com/luispolis124/AnimalForest64-Recomp.git
   cd AnimalForest64-Recomp
   ```
2. Configure the project using CMake with a modern toolchain (such as llvm-mingw or MSVC).
3. Build the target executable.
