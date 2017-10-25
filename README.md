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

### Credentials

You will need a GitLab API token ([get here](https://docs.gitlab.com/ce/user/profile/personal_access_tokens.html)) and the project ID from `/api/v4/projects?search=[name]&private_token=`.

### Commands

From `build/` folder.

```
$ env $(cat ../.env | xargs) ./getstatus
```

Convenience build and run command (from root directory):

```
make -C build/ && env $(cat .env | xargs) ./build/getstatus
```
