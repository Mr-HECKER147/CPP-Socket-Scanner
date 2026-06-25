# Socket Scanner

A lightweight, cross-platform port scanner written in C++20. Quickly check if specific ports are open on localhost or any target host using non-blocking TCP connections.

## Features

- **Cross-platform** — works on Windows, Linux, and macOS
- **Non-blocking connections** — efficient port checking with configurable timeouts
- **Simple to use** — scans a predefined list of common ports (HTTP, HTTPS, SSH, MySQL, PostgreSQL, etc.)
- **C++20** — modern C++ standards
- **CMake build** — easy configuration and compilation

## Prerequisites

- **CMake** 3.8 or higher
- **C++20 compiler** (MSVC, GCC, or Clang)
- **Ninja** build generator (or compatible alternative)
- **Windows**: Visual Studio 2022 or Build Tools
- **Linux/macOS**: GCC/Clang with standard development libraries

## Building

### Visual Studio 2022

1. Open the folder: **File > Open > Folder** → select this project
2. Visual Studio will auto-detect CMake
3. Select a preset from the configuration dropdown: `x64-debug`, `x64-release`, `x86-debug`, or `x86-release`
4. Build: **CMake > Build All** or press **Ctrl+Shift+B**

### Command Line
