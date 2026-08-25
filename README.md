# AnimalForest64-Recomp

An experimental native static recompilation project for the classic N64 game **Animal Forest (Dōbutsu no Mori)** utilizing modern tools like **N64Recomp**, **N64ModernRuntime**, and **RT64**.

This project transforms the original MIPS assembly code into native high-performance binaries, enabling enhanced framerates, modern rendering features, widescreen support, and high-performance native execution.

⚠️ **Legal Disclaimer**
This project does **NOT** include the game ROM. To compile and run this project, you must possess a legal copy of the original *Dōbutsu no Mori* (N64) ROM (`baserom.z64`). This repository provides only the configuration files, scripts, and build structures necessary to perform the recompilation process.

---

## 🛠️ Requirements & Dependencies

To build and recompile this project, you will need:
* **CMake** (3.20 or higher)
* **Python 3**
* **Git**
* A modern C++ compiler supporting C++20 (MSVC, GCC, or Clang)
* **N64Recomp** toolchain and runtime dependencies.

---

## 🚀 How to Build & Compile

1. **Clone the repository:**
   ```bash
   git clone [https://github.com/luispolis124/AnimalForest64-Recomp.git](https://github.com/luispolis124/AnimalForest64-Recomp.git)
   cd AnimalForest64-Recomp

 * Add your original ROM:
   Place your legal ROM (named strictly as baserom.z64) into the root directory of the project.
 * Configure the project with CMake:
   mkdir build
cd build
cmake ..

 * Build the native port:
   cmake --build . --config Release

✨ Features
 * Native Recompilation: Converts original N64 MIPS machine code into native executables via N64Recomp.
 * Modern Enhancements: Powered by RT64 and N64ModernRuntime for advanced graphics, modern input handling, and high-framerate support.
 * Preservation & Modding: Built as a robust foundation for translations, quality-of-life mods, and community-driven improvements.
🤝 Contributions
Contributions are very welcome! If you would like to help improve the code, fix bugs, or add new features, feel free to open an issue or submit a Pull Request.
📄 License
This project is licensed under the MIT License - see the LICENSE file for more details.
