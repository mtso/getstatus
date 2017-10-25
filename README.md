# getstatus

GitLab JSON API fetcher.

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

## Running

From `build/` folder.
```
$ env $(cat ../.env | xargs) ./getstatus
```
