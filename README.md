# Lab of Microcomputer Principles and Applications

106.1【電子系】ET3801301 微算機原理及應用實習 / Lab. of Microcomputer Principles and Applications

This repository contains laboratory materials and example projects for an 8051-based microcontroller course. Each lab folder includes Keil µVision project files and C source code demonstrating fundamental concepts such as GPIO, timers, interrupts, and serial communication.

如果你正在修習「微算機原理及應用實習」，本倉庫提供各次實驗的 Keil 專案與 C 範例程式，方便你在 µVision 中直接開啟、編譯與除錯。

## Prerequisites

- Keil µVision (C51 toolchain) installed on Windows
- 8051-compatible target or simulator
- Optional: TE-8051A 實驗板（本倉庫提供 `TE-8051A.zip` 資源）

## Quick Start

1. Clone the repository.
2. Open the corresponding `*.uvproj` file for a lab in Keil µVision.
3. Build: Project → Rebuild all target files.
4. Run/Debug: Debug → Start/Stop Debug Session (simulate) or download to board as applicable.

## Repository Layout

- `labX/`, `labX_Y/`: Lab folders. Each typically contains:
  - `*.uvproj`, `*.uvopt`, `*.uvgui.*`: Keil µVision project/config files
  - `*.c`: Source code for the lab
  - `Listings/`: Compiler listing outputs
  - `Objects/`: Build artifacts (e.g., `.hex`, `.obj`, logs)
- Presentation and documentation files (e.g., `Lab1.pptx`, `Lab4.doc`, etc.)
- `TE-8051A.zip`: Board-related reference materials or tools

Example folders in this repo include `lab2`, `lab2_2`, `lab2_3`, `lab2_4`, `lab3`, `lab3_2`, `lab4`, `lab5`, `lab6`.

## Build and Run (Keil µVision)

1. Open the lab’s `*.uvproj` in Keil µVision.
2. Select the correct target/device if prompted.
3. Build via Project → Rebuild all target files.
4. Output artifacts (e.g., `.hex`) will be generated under the lab’s `Objects/` directory.
5. To simulate, use Debug → Start/Stop Debug Session and the built-in peripherals.
6. To program hardware, use your board’s programming workflow (e.g., ISP/USB programmer) and load the generated `.hex`.

## Notes

- Some folders contain multiple variants of a lab (e.g., `lab3` and `lab3_2`). Open the specific project you need.
- File names and device selections may differ across campus/lab setups. Adjust the Keil target settings to match your MCU/board.
- If you see path issues when opening a project, use Project → Manage → Project Items to fix source/include paths.

## Troubleshooting

- Build errors about missing device or toolchain: Ensure Keil C51 and the target device pack are installed via Pack Installer.
- Cannot open project: Verify you opened the `*.uvproj` file within the correct lab folder.
- No `.hex` generated: Make sure the target is configured to produce a hex file (Options for Target → Output → Create HEX File).

## License

Unless otherwise specified by course staff, materials are provided for educational use.

## Acknowledgements

Course: ET3801301 微算機原理及應用實習
Hardware: 8051/TE-8051A (where applicable)
