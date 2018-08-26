# graph-slam

A toy project for experimenting with modern CMake and C++17 features.

## Build Statuses
OS|Build Status
--|------------
Linux|[![Build Status]( https://travis-ci.org/aharrison24/cpp-graph-slam.svg?branch=master)](https://travis-ci.org/aharrison24/cpp-graph-slam)

## Requirements
The project needs a recent version of CMake to build.

### Dependencies
Project dependencies are currently unstable. You can see what they are by looking
for `find_package` calls in the top-level `CMakeLists.txt` file.

The easiest way to install the project dependencies is to use the [Conan package
manager](https://conan.io/).

### Installing dependencies with homebrew
```bash
brew install sfml
```

### Installing dependencies with conan
```bash
# Install conan
pip3 install conan

# Add extra remotes
conan remote add bincrafters https://api.bintray.com/conan/bincrafters/public-conan
conan remote add aharrison24 https://api.bintray.com/conan/aharrison24/conan-stuff

# Install conan dependencies
cd <build_dir>
conan install <source_dir> --build missing
```

If the `conan_paths.txt` file in the source directory changes, then it will be
necessary to re-run the `conan install ...` command. The build system will detect
if this needs to be done and let you know about it by throwing an error. You can
optionally get the build system to automatically run the `conan install` step by
setting the `CONAN_AUTO_UPDATE` CMake cache variable.

NOTE: Once CMake has found a dependency, it won't search for it again unless you
clear the corresponding variables in the cache. If a library version in the
conanfile is updated, it will be necessary to delete the corresponding cache
variables to force CMake to do a fresh search for the library. In practice it may
be easier to just delete the `CMakeCache.txt` file and regenerate it.

## Using pre-commit hooks
This project uses the [pre-commit](https://pre-commit.com/) tool to perform
linting checks. Install them as follows:

```bash
# Install pre-commit tool
pip3 install pre-commit

cd <src-dir>

# Install pre-commit linters
pre-commit install --install-hooks

# Install git commit linter
pre-commit install --hook-type commit-msg
```
