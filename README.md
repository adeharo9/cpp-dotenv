# cpp-dotenv

![version 0.3.0](https://img.shields.io/badge/version-0.3.0-blue)

C++ implementation of NodeJS [dotenv](https://github.com/motdotla/dotenv) project. Loads environment variables from `.env` for C++ projects.

**Please take into account this is still a developing project.**

**cpp-dotenv** is implemented as a single C++ header file, so there is no need to compile nor to add complex file dependencies to your project. Simply include the header file wherever you want to use it and ta-da!, you're done.

## Table of contents

1. [Dependencies](#dependencies)
2. [Usage](#usage)
   1. [CMake](#cmake)
3. [Examples](#examples)
   1. [Basic usage](#basic-usage)
   2. [Reference renaming](#reference-renaming)
   3. [Several dotenv files](#several-dotenv-files)
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

By default, already-defined environment variables are not overwritten even if redefined in some of the loaded files. This behavior can be changed, however, by calling the `load_config()` function with the `overwrite` parameter set to `true`. For an example, take a look at [this one](#several-dotenv-files).

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

### Basic usage

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
    cout << "DB_NAME: " << env["DB_NAME"] << endl;
    cout << "eval \"" << env["COMMAND"] << " " << env["HOST"] << "\"" << endl;
}
```

would produce the following output:

```shell
$ ./main
  DB_NAME: DontDoThisAtHome
  eval "ping 8.8.8.8"
```

### Reference renaming

Assuming the same `.env` file as in the [previous case](#basic-usage), the predefined `env` reference can be easily renamed and used just exactly as the original one.

The following code:

```cpp
#include "dotenv.h"
#include <iostream>

using namespace std;

int main()
{
    auto& dotenv = dotenv::env;
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

### Several dotenv files

The situation of having several different dotenv files is no stranger one (`.env` for private configuration variables, `.pubenv` for public variables, etc.). Loading several files in addition to the default one and overwritting any variables that are redefined on the files can be done as follows:

Assume the following `.env` file:

```env
# DB THINGS
DB_NAME=DontDoThisAtHome
DB_PASS=such_security
```

And the following `.pubenv` file:

```env
# CONNECTIONS THINGS
COMMAND=ping
HOST=8.8.8.8
MESSAGE="Hey buddy!"
```

The following source file:

```cpp
#include "dotenv.h"
#include <iostream>

using namespace dotenv;
using namespace std;

int main()
{
    env.load_dotenv(".env", true);
    env.load_dotenv(".pubenv", true);
    cout << "DB_NAME: " << env["DB_NAME"] << endl;
    cout << "eval \"" << env["COMMAND"] << " " << env["HOST"] << "\"" << endl;
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

## Known issues

The complete list of issues can be consulted at the [issues page](https://github.com/adeharo9/cpp-dotenv/issues).

1. [Variable resolution on values not yet vailable](https://github.com/adeharo9/cpp-dotenv/issues/3)
