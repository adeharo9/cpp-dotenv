# [C++ .ENV](https://github.com/adeharo9/cpp-dotenv)

<img src="https://raw.githubusercontent.com/adeharo9/cpp-dotenv/master/cpp-dotenv.png" alt="cpp-dotenv" align="right"/>

![v1.0.0-alpha](https://img.shields.io/badge/version-v1.0.0--alpha-blue "v1.0.0-alpha")
![BSD 3-clause license](https://img.shields.io/badge/license-BSD%203--clause-green "BSD 3-clause license")

Loads environment variables from `.env` files for C++ projects.

C++ implementation of NodeJS [dotenv](https://github.com/motdotla/dotenv) project. `load_dotenv()` method API inspired by Python's [python-dotenv](https://pypi.org/project/python-dotenv/) port of the dotenv project.

> _**NOTE: please take into account this is still a developing project.**_

## Table of contents

1. [Dependencies](#dependencies)
2. [Build](#build)
   1. [CMake](#cmake)
3. [Usage](#usage)
   1. [`load_dotenv()` method](#load_dotenv-method)
4. [Features](#features)
   1. [Error reporting](#error-reporting)
   2. [Escape sequence expansion](#escape-sequence-expansion)
   3. [Variable overwritting](#variable-overwritting)
   4. [Variable resolution](#variable-resolution)
5. [Examples](#examples)
   1. [Basic usage](#basic-usage)
   2. [Reference renaming](#reference-renaming)
   3. [Several dotenv files](#several-dotenv-files)
   4. [Variable resolution](#variable-resolution-1)
6. [Known limitations](#known-limitations)
7. [Grammar](#grammar)

## Dependencies

**NONE**, for sure! :sunglasses: If it had any, it wouldn't follow the basic dotenv principles. All the needed libraries are shipped with this repository right out of the box.

## Build

Supported build methods are:

- [CMake](#cmake) (>=3.10)

### CMake

**cpp-dotenv** comes with support for `CMake` right out of the box. In order to use it, simply include this repository's directory and link the `cpp_dotenv` target to your own targets where needed:

```cmake
add_subdirectory(cpp-dotenv)
```

```cmake
target_link_libraries(YOUR_TARGET cpp_dotenv)
```

After this, you might use the library as described in [usage](#usage); no extra scoping, no need to worry about the project's directory structure.

## Usage

To be able to use the dotenv classes, simply include the main header file:

```cpp
#include "dotenv.h"
```

For the sake of simplycity (and if your project namespace density allows to), you can also use the `dotenv` namespace under which all definitions are placed:

```cpp
using namespace dotenv;
```

In order to bring your environment variables from your configuration files, simply make as many calls to the `load_dotenv()` method as needed with the appropriate paths (either relative to your executable's path or absolute) and arguments.

```cpp
env.load_dotenv();
```

Not passing any argument to the function is equivalent to tell **cpp-dotenv** to search for a file named `.env` at the same level as the executable that is making the call to the function.

For your convenience, there is a namespace-global reference variable to the `dotenv` singleton class instance named `env`. Simply use it as you would use a dotenv object on NodeJS, or you can define your own references:

```cpp
auto& dotenv = env; // 'auto' here is 'dotenv::dotenv'
```

### `load_dotenv()` method

The `load_dotenv()` method, part of `class dotenv`, is declared in the [`include/dotenv.h`](/include/dotenv.h) file. Since all of its parameters have default values, it can be called with any number of arguments.

#### Signature

```cpp
dotenv& load_dotenv(const std::string& dotenv_path = ".env",
                    const bool overwrite = false,
                    const bool interpolate = true);
```

#### Parameters

- `dotenv_path`: path string, absolute or relative to the executable calling the function, of the dotenv file to be loaded. Default is `".env"`.
- `overwrite`: boolean representing whether or not to overwrite already-defined environment variables at loading time. Default is `false`.
- `interpolate`: boolean representing whether or not to resolve in-value variable references. Default is `true`.

#### Return

A reference to the `class dotenv` `this` object being used is returned, which allows for concatenating several `load_dotenv()` calls and serially load files.

## Features

The **cpp-dotenv** library has the following built-in features:

- [Error reporting](#error-reporting)
- [Escape sequence expansion](#escape-sequence-expansion)
- [Variable overwritting](#variable-overwritting)
- [Variable resolution](#variable-resolution)

### Error reporting

**cpp-dotenv** reports and handles four different types of errors:

- **Lexer errors**: errors produced by an incorrect format of the input language, i.e. usage of language features that do not belong to the dotenv syntax. This kind of errors throw irrecoverable exceptions.
- **Parsing errors**: errors produced by an incorrect use of the input language, i.e. the language syntax itself is correct, but it is used in an unexpected way. This kind of errors invalidate the variable they occurr in, making it to become as if it was not defined, but allowing the loading process to recover and continue.
- **Circular reference errors**: errors produced by variables that define a cycle of references, which are ultimately not resolved and their references are deleted from all the corresponding values. The variables they occurr in are ultimately defined as without the cycling references.
- **Undefined external reference warnings**: warnings produced by references to externally-loaded variables that are not present in the host environment. This variables are ultimately assigned their value as the empty string.

### Escape sequence expansion

Escape sequence expansion happens in all of the loaded values (both string and raw form) right at the end of the loading process, after the variable resolution has already been performed.

Typical one-character escape sequences are supported (`\n`, `\t`, `\\`, etc.). Dotenv-spefic escape sequences are:

| Character | Escape sequence |
| :-------: | :-------------: |
| `=`       | `\=`            |
| `$`       | `\$`            |
| `#`       | `\#`            |

> _NOTE: escape sequences on externally-loaded variables **ARE NOT EXPANDED**._

### Variable overwritting

By default, already-defined environment variables are not overwritten even if redefined in some of the loaded files.

This behavior can be changed, however, by calling the [`load_dotenv()` method](#load_dotenv-method) with the [`overwrite` parameter](#parameters) set to `true`. For an example on how to use it, take a look at [this one](#several-dotenv-files).

### Variable resolution

**cpp-dotenv** by default resolves variables nested inside variable definitions in the parsed files, both with those defined in the file being loaded or already present in the hosting environment itself.

- Variable reference with variables declared in the **same file** is order-independent: there's no need to worry about the declaration order of the variables inside a same file, **cpp-dotenv** will resolve all of the symbols regardless of their order of declaration.
- Variable reference with variables declared on **different files** is order-depdendent on the loading order of the files via the `load_dotenv()` method: variables defined in later calls to `load_dotenv()` are not yet visible to files being processed at a previous load and will be treated as external variables.

Variable resolution can be explicitly turned off by setting the [`interpolate` parameter](#parameters) of the [`load_dotenv()` method](#load_dotenv-method) to `false`.

> _NOTE: variable references inside externally-loaded variables **ARE NOT RESOLVED**._

There are two different types of supported variable references:

- **Raw-style unbounded references** of the style `$VAR_NAME`, which only support references composed by letters, numbers and underscores. Their name must start by a letter or by an underscore, and have at least one character.
- **Bounded references**, of the style `${VAR_NAME}`, which support a wider set of character possibilities.

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
    env.load_dotenv();
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

Assuming the same `.env` file as in the [previous case](#basic-usage), the predefined `env` reference can be easily renamed and used just exactly as the original one. The `load_dotenv()` method also returns a reference to the object it is being applied to, so it can be easily nested in a case like this.

The following code:

```cpp
#include "dotenv.h"
#include <iostream>

using namespace std;

int main()
{
    auto& dotenv = dotenv::env.load_dotenv();
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

The situation of having several different dotenv files is no stranger one (`.env` for private configuration variables, `.pubenv` for public variables, etc.). Loading several files and overwritting any variables that are redefined on the files can be done as follows:

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
    env.load_dotenv(".env", true).load_dotenv(".pubenv", true);
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

### Variable resolution

Assume an environment variable `${HOST}` already defined on the host environment as `myweb.com` and the following `.env` file:

```env
# FULL URL
URL=${URL_PROT}://${HOST}/${URL_SUBD}

# PARTIAL DEFINITIONS
URL_PROT=https
URL_SUBD=some/sub/page.html
```

The following `.cpp` file:

```cpp
#include "dotenv.h"
#include <iostream>

using namespace dotenv;
using namespace std;

int main()
{
    env.load_dotenv();
    cout << "URL: " << env["URL"] << endl;
}
```

would produce the following output:

```shell
$ ./main
  URL: https://myweb.com/some/sub/page.html
```

## Known limitations

- _Arbitrary octal value escape sequences are not expanded._
- _Arbitrary hexadecimal value escape sequences are not expanded._
- _Arbitrary unicode value escape sequences are not expanded._

## Grammar

For the geeks, you can check the implemented grammars and all of the ANTLR-related files on the [`common/antlr/` directory](/common/antlr).
