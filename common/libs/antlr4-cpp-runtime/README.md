# [ANTLR4 C++ runtime](https://github.com/adeharo9/antlr4-cpp-runtime)

![version 4.8](https://img.shields.io/badge/version-4.8-blue "version 4.8")
![BSD 3-clause license](https://img.shields.io/badge/license-BSD%203--clause-green "BSD 3-clause license")

This project holds a copy of the [ANTLR4 C++ runtime](https://github.com/antlr/antlr4/tree/4.8/runtime/Cpp) as a standalone library, in order to be imported and to be linked to by means of CMake targets.

The source code under the `runtime/src` directory comes directly from the [official ANTLR4 C++ runtime](https://github.com/antlr/antlr4/tree/4.8/runtime/Cpp).

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

The `master` branch on this repository is always (at least) up-to-date with the latest tag available, and thus is stable.

Tag versions correspond to those on the [official ANTLR4 repository](https://github.com/antlr/antlr4). The following tags are available:

- [4.8](https://github.com/adeharo9/antlr4-cpp-runtime/tree/4.8)

## Dependencies

- C++ compiler with support for (at least) C++11
- [CMake](https://cmake.org/) (>=3.0)
- [Make](https://www.gnu.org/software/make/)

## Installation

This library is standalone and autocontained; it does not have any dependencies on external libraries. To start using it, simply add this repository as a subtree or submodule in your own project's structure.

## Build

Supported build methods are:

- [CMake](#cmake)

### CMake

To configure building with CMake, simply add the subdirectory where this repository resides in your `CMakeLists.txt` file. Both the target `antlr4_cpp_runtime` and the symbol `ANTLR4_CPP_RUNTIME` will be available; they are autocontained and simply need to be linked to in your own targets, wherever an ANTLR4 header is used. No need to further action, nor to include any directories.

```cmake
add_subdirectory(antlr4-cpp-runtime)
```

```cmake
target_link_libraries(YOUR_TARGET
    antlr4_cpp_runtime
)
```

After this, simply build as usual:

```shell
mkdir build && cd build
cmake .. && make -j
```

Since the runtime takes quite a while to compile, consider building with `make -j` to speed up the process.
