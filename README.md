# [C++ .ENV](https://github.com/adeharo9/cpp-dotenv)

![version 0.3.0](https://img.shields.io/badge/version-0.3.0-blue "version 0.3.0")
![BSD 3-clause license](https://img.shields.io/badge/license-BSD%203--clause-green "BSD 3-clause license")

C++ implementation of NodeJS [dotenv](https://github.com/motdotla/dotenv) project. Loads environment variables from `.env` files for C++ projects.

**Please take into account this is still a developing project.**

## Table of contents

1. [Dependencies](#dependencies)
2. [Usage](#usage)
   1. [CMake](#cmake)
   2. [Variable resolution](#variable-resolution)
3. [Examples](#examples)
   1. [Basic usage](#basic-usage)
   2. [Reference renaming](#reference-renaming)
   3. [Several dotenv files](#several-dotenv-files)
   4. [Variable resolution](#variable-resolution-1)
4. [Grammar](#grammar)

## Dependencies

**NONE**, for sure! :sunglasses: If it had, it wouldn't follow the basic dotenv principles. All the needed libraries are shipped with this repository right out of the box.

## Usage

To be able to use the dotenv classes, simply include the header file:

```cpp
#include "dotenv.h"
```

For the sake of simplycity (and if your project namespace density allows to), you can also use the `dotenv` namespace under which all definitions are:

```cpp
using namespace dotenv;
```

In order to bring your environment variables from your configuration files, simply make as many calls to the `load_dotenv(const std::string& dotenv_path)` function as needed with the appropriate paths (either relative or absolute).

```cpp
env.load_dotenv();
```

Not passing any parameter to the function is equivalent to tell **cpp-dotenv** to search for a file named `.env` at the same level as the executable that is making the call to the function.

---

By default, already-defined environment variables are not overwritten even if redefined in some of the loaded files. This behavior can be changed, however, by calling the `load_config()` function with the `overwrite` parameter set to `true`. For an example, take a look at [this one](#several-dotenv-files).

Also for convenience, there is a namespace-global pre-loaded reference variable to the `dotenv` singleton class instance named `env`. Simply use it as you would use a dotenv object on NodeJS, or you can define your own references:

```cpp
auto& dotenv = env; // 'auto' here is 'dotenv::dotenv'
```

### CMake

`cpp-dotenv` also comes with support for `CMake` right out of the box. In order to use it, simply include this repository's directory and link the `cpp_dotenv` target to your own targets where needed (the target is also available under the symbol `CPP_DOTENV`):

```cmake
add_subdirectory(cpp-dotenv)
```

```cmake
target_link_libraries(YOUR_TARGET cpp_dotenv)
```

After this, you might use the library as described in [usage](#usage); no extra scoping, no need to worry about the project's directory structure.

### Variable resolution

Now **cpp-dotenv** by default resolves variables nested inside variable definitions in the parsed files, both with those defined in the file being loaded or already present in the environment itself.

Variable reference with variables declared in the same file is order-independent: there's no need to worry about the declaration order of the variables, **cpp-dotenv** will resolve all the symbols regardless of their order of declaration in a same file.

Variable reference with variables declared on different files is order-depdendent on the loading order of the files via the `load_dotenv()` function: variables defined in later calls to `load_dotenv()` are not yet visible to files being processed at a specific moment.

Variable resolution can be explicitly turned off by setting the `interpolate` positional parameter of the `load_dotenv()` method to `false`.

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

Assuming the same `.env` file as in the [previous case](#basic-usage), the predefined `env` reference can be easily renamed and used just exactly as the original one. The `load_dotenv()` function also returns a reference to the object it is being applied to, so it can be easily nested in a case like this.

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

### Variable resolution

Assume the following `.env` file:

```env
# PARTIAL DEFINITIONS
URL_PROT=https
URL_ADDR=myweb.com
URL_SUBD=some/sub/page.html

# FULL URL
URL=${URL_PROT}://${URL_ADDR}/${URL_SUBD}
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

## Grammar

For the geeks, you can check the grammars I've implemented on the `antlr/grammar/` directory.
