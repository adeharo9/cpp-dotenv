# dotenvcpp
c++ implementation of nodejs [dotenv](https://github.com/motdotla/dotenv) project. Loads environment variables from .env for c++ projects.

**dotenvcpp** is implemented as a single C++ header file, so there is no need to compile nor to add complex file dependencies to your project. Simply include the header file wherever you want to use it and ta-da!, you're done.

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
For convenience, **dotenvcpp** auto-configures the dotenv object (which is instance of the singleton class `dotenv`) by calling `dotenv.config()` at the very beginning of your file (just right before the end of `dotenv.h`), although if you need to reload simply re-run the configuration; everything new will show up on your dotenv instance.

Also for convenience, there is a namespace-global pre-loaded reference to the dotenv class singleton instance, named `env`. Simply use it as you would use a dotenv object on nodejs, or you can define your own references:
```
auto& dotenv = env; // 'auto' here is 'dotenv::dotenv'
```

## Grammar
For the geeks, you can check the grammar I've implemented on the `grammar/env.g4` file. Despite being written in an ANTLR4 fashion, I've implemented a simple recursive parser myself given the basic nature of the language. It is available under the `dotenv::parser` class.