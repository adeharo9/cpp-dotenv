# ANTLR4 C++ runtime

![version 4.8](https://img.shields.io/badge/version-4.8-blue "version 4.8")

This project holds a copy of the [ANTLR4 C++ runtime](https://github.com/antlr/antlr4/tree/4.8/runtime/Cpp) as an independent repository, in order to be imported as submodule or subtree and to be linked to by means of CMake targets.

This version of the ANTLR4 C++ runtime **is intended to**:

- Be linked to in any project using ANTLR4-generated C++ code.
- Be shipped as part of any project where the ANTLR4 C++ runtime is a dependency.
- Be as lightweight as possible, including only the necessary `.h` and `.cpp` files

This version of the ANTLR4 C++ runtime **is not intended to**:

- Generate C++ code from ANTLR4 grammars.
- Interact with the ANTLR4 tool.

## Table of contents

1. [Supported versions](#supported-versions)
2. [Dependencies](#dependencies)
3. [Installation](#installation)
4. [Build](#build)
    1. [CMake](#cmake)

## Supported versions

The `master` branch is always up-to-date to the latest tag available on this repository.

The following tags are available:

- 4.8

## Dependencies

- Compiler with support for C++11
- CMake (>=3.0)
- Make

## Installation

Simply add this repository as submodule or subtree in your own project's structure.

## Build

Supported build methods are:

- CMake

### CMake

Simply add the subdirectory where this repository resides. The symbol `ANTLR4_CPP_RUNTIME` will be available; it is autocontained and simply needs to be linked to in your own targets, wherever an ANTLR4 header is used. No need to include directories.

```cmake
add_subdirectory(antlr4-cpp-runtime)

...

target_link_libraries(${YOUR_OWN_LIB_OR_EXE}
    ${ANTLR4_CPP_RUNTIME}
)
```
