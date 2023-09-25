This is clearly not right. Needs iterating.

### Conan profile (clang16)
```
[settings]
arch=x86_64
build_type=Release
compiler=clang
compiler.cppstd=23
compiler.libcxx=libc++
compiler.version=16
os=Macos

[buildenv]
CC=/usr/local/opt/llvm@16/bin/clang
CXX=/usr/local/opt/llvm@16/bin/clang++
```

### Set up build directory
```
export CXX=/usr/local/opt/llvm@16/bin/clang++
export CC=/usr/local/opt/llvm@16/bin/clang

# <Activate a venv here>

pip install conan==2.0.11

cd src
# TODO: Might need --install-folder instead of --output-folder?
conan install  . --build=missing --profile:build=clang16 --profile:host=clang16 --output-folder=../build

cd ../build
# Rexport env vars if you're in a different shell
cmake -GNinja -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_COMPILER_LAUNCHER=$(which ccache) -DCMAKE_TOOLCHAIN_FILE=build/Release/generators/conan_toolchain.cmake ../src
```