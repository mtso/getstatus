# Basic JSON Boilerplate

## Requirements

The only explicit requirement is a C++11 compatible compiler such as clang or gcc. The minimum required version of gcc is unknown, though, so let me know of any trouble building with a specific version of gcc.

## Building

This project and C++ Requests both use CMake. The first step is to make sure all of the submodules are initialized:

```
$ git submodule update --init --recursive
```

Then make a build directory and do a CMake build from there:

```
$ mkdir build
$ cd build
$ cmake ..
$ make
```