# cpp-dotenv

C++ implementation of nodejs [dotenv](https://github.com/motdotla/dotenv) project. Loads environment variables from .env for C++ projects.

**Please take into account this is still a developing project.**

**cpp-dotenv** is implemented as a single C++ header file, so there is no need to compile nor to add complex file dependencies to your project. Simply include the header file wherever you want to use it and ta-da!, you're done.

## Table of contents

1. [Dependencies](#dependencies)
2. [Usage](#usage)
   1. [CMake](#cmake)
3. [Examples](#examples)
4. [Grammar](#grammar)

## Dependencies

**NONE**, for sure! :sunglasses: If it had, it wouldn't follow the basic dotenv principles.

## Usage

To be able to use the dotenv classes, simply include the header file:

```cpp
#include "dotenv.h"
```

For the sake of simplycity (and if your project namespace density allows to), you can also use the `dotenv` namespace under which all definitions are:

```cpp
using namespace dotenv;
```

For convenience, **cpp-dotenv** auto-configures a class object (which is instance of the singleton class `dotenv`) by calling the `load_dotenv()` method at the very beginning of your file (just right before the end of `dotenv.h`) and trying to load a `.env` file, although if you need to add-in your own files (like `.myenv`), simply re-run the loading step passing the file name as parameter; everything new will show up on the `dotenv` instances.

Also for convenience, there is a namespace-global pre-loaded reference variable to the `dotenv` singleton class instance named `env`. Simply use it as you would use a dotenv object on NodeJS, or you can define your own references:

```cpp
auto& dotenv = env; // 'auto' here is 'dotenv::dotenv'
```

### CMake

`cpp-dotenv` also comes with support for `CMake` right out of the box. In order to use it, simply include this repository's directory and link the `CPP_DOTENV_LIB` library to your own targets where needed:

```cmake
add_subdirectory(cpp-dotenv)
```

```cmake
target_link_libraries(YOUR_TARGET ${CPP_DOTENV_LIB})
```

After this, you might use the library as described in [usage](#usage); no extra scoping, no need to worry about the project's directory structure.

## Examples

Assume the following `.env` file:

```env
# DB THINGS
DB_NAME=DontDoThisAtHome
DB_PASS=such_security

# CONNECTIONS THINGS
COMMAND=ping
HOST=8.8.8.8
MESSAGE="Hey buddy!"
```

The following `.cpp` file:

```cpp
#include "dotenv.h"
#include <iostream>

using namespace dotenv;
using namespace std;

int main()
{
    auto& dotenv = env;  // Reference re-naming

    cout << "DB_NAME: " << dotenv["DB_NAME"] << endl;
    cout << "eval \"" << dotenv["COMMAND"] << " " << dotenv["HOST"] << "\"" << endl;
}
```

would produce the following output:

```shell
$ ./main
  DB_NAME: DontDoThisAtHome
  eval "ping 8.8.8.8"
```

## Grammar

For the geeks, you can check the grammar I've implemented on the `grammar/env.g4` file. Despite being written in an ANTLR4 fashion, I've implemented a simple recursive parser myself given the basic nature of the language. The parser and its methods are publicly available under the `dotenv::parser` class.
