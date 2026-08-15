# AnimalForest64-Recomp

A decompilation and recompilation project for the classic N64 game **Animal Forest (Dōbutsu no Mori)**.

This project utilizes `splat` and modern N64 toolchains to extract, build, and run the game natively or through high-performance emulation environments.

⚠️ **Legal Disclaimer**
This project does **NOT** include the game ROM. To compile and run this project, you must possess a legal copy of the original *Dōbutsu no Mori* (N64) ROM (`baserom.z64`). This repository provides only the configuration files (`animalforest.yaml`), scripts, and tools necessary to perform the extraction and build process.

---

## 🛠️ Requirements & Dependencies

To build this project, you will need:
* **Python 3**
* **Git**
* **Make** and build tools (`build-essential`)
* Python dependencies required by splat and decompilation tools:
  ```bash
  pip install -r splat/requirements.txt

🚀 How to Build & Compile
 * Clone the repository:
   git clone [https://github.com/luispolis124/AnimalForest64-Recomp.git](https://github.com/luispolis124/AnimalForest64-Recomp.git)
cd AnimalForest64-Recomp

 * Add your original ROM:
   Place your legal ROM (named strictly as baserom.z64) in the root directory of the project.
 * Extract the assets:
   Run the splitting script to extract the code and assets:
   python3 splat/split.py animalforest.yaml

 * Compile the ROM:
   Run the build process to generate the new ROM inside the build/ directory:
   make

✨ Features
 * Accurate Reconstitution: Rebuilds the N64 ROM bit-by-bit from source and assets.
 * Modern Tooling: Uses modern Python-based splitting and assembly tools (splat).
 * Preservation & Modding: Foundation for future mods, translations, and modern hardware enhancements.
🤝 Contributions
Contributions are very welcome! If you would like to help improve the code, fix bugs, or add new features, feel free to open an issue or submit a Pull Request.


📄 License
This project is licensed under the MIT License - see the LICENSE file for more details.
