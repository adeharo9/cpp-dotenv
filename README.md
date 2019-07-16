# cpp-dotenv
c++ implementation of nodejs [dotenv](https://github.com/motdotla/dotenv) project. Loads environment variables from .env for c++ projects.

**Please take into account this is still a developing project.**

**cpp-dotenv** is implemented as a single C++ header file, so there is no need to compile nor to add complex file dependencies to your project. Simply include the header file wherever you want to use it and ta-da!, you're done.

## Dependencies
**NONE**, for sure! :sunglasses: If it had it wouldn't follow the basic dotenv principles.

## Usage
To be able to use the dotenv classes, simply include the header file:
```
#include "dotenv.h"
```
For the sake of simplycity (and if your project namespace density allows to), you can also use the `dotenv` namespace under which all definitions are:
```
using namespace dotenv;
```
For convenience, **cpp-dotenv** auto-configures the `dotenv` class object (which is instance of the singleton class `dotenv`) by calling `dotenv.config()` at the very beginning of your file (just right before the end of `dotenv.h`), although if you need to reload the environment simply re-run the configuration; everything new will show up on the `dotenv` instance.

Also for convenience, there is a namespace-global pre-loaded reference variable to the `dotenv` singleton class instance, named `env`. Simply use it as you would use a dotenv object on nodejs, or you can define your own references:
```
auto& dotenv = env; // 'auto' here is 'dotenv::dotenv'
```
## Examples
Assume the following `.env` file:
```
# DB THINGS
DB_NAME=DontDoThisAtHome
DB_PASS=such_security

# CONNECTIONS THINGS
COMMAND=ping
HOST=8.8.8.8
MESSAGE="Hey buddy!"
```
The following `.cpp` file:
```
#include "dotenv.h"
#include <iostream>

using namespace std;
using namespace dotenv;

int main()
{
    auto& dotenv = env;  // Reference re-naming

    cout << "DB_NAME: " << dotenv["DB_NAME"] << endl;
    cout << "eval \"" << dotenv["COMMAND"] << " " << dotenv["HOST"] << "\"" << endl;
}
```
would produce the following outputs:
```
$ ./main
  DB_NAME: DontDoThisAtHome
  eval "ping 8.8.8.8"

$
```

## Grammar
For the geeks, you can check the grammar I've implemented on the `grammar/env.g4` file. Despite being written in an ANTLR4 fashion, I've implemented a simple recursive parser myself given the basic nature of the language. The parser and its methods are publicly available under the `dotenv::parser` class.
