AnimalForest64-Recomp
A native PC recompilation project for the classic N64 game Animal Forest (Dōbutsu no Mori).

This project utilizes Splat and recompilation tools to allow the game to run natively on modern hardware, providing better performance and support for higher resolutions.

⚠️ Legal Disclaimer
This project does NOT include the game ROM. To compile and run this project, you must possess a legal copy of the original Dōbutsu no Mori (N64) ROM. This repository provides only the configuration files (animalforest.yaml), source code, and tools necessary to perform the extraction and build process from your own copy of the ROM.

How to Compile
 * Ensure you have Python and all required dependencies installed (spimdisasm, crunch64, intervaltree, etc.).
 * Place your original ROM (named baserom.z64) in the root directory of the project.
 * Run the splitting script to extract the assets:
python3 splat/split.py animalforest.yaml

Features
 * Native Execution: Play the game without needing an emulator, with superior performance.
 * Preservation: Maintains the fidelity of the original game on modern hardware.
Contributions
Contributions are very welcome! If you would like to help improve the code, fix bugs, or add new features, feel free to open an issue or submit a Pull Request.

License
This project is licensed under the MIT License - see the LICENSE file for more details.
