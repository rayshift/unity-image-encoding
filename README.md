## C# ETC1/ETC2 Encoding
This library enables encoding ETC1/ETC2 for use in mobile games (such as those based on Unity or cocos2d) in C# via a set of [CppSharp](https://github.com/mono/CppSharp) bindings to [etcpak](https://github.com/wolfpld/etcpak). It is fully cross-platform (tested on Windows x64, Linux x64) and should support ARM64 with minimal modifications.

## Developer Information
Ensure when you clone the repository you also clone submodules. (i.e. `git clone --recurse-submodules`)

### Building Native Libraries
If your target platform does not support AVX2 and you are compiling using MSVC, you will need to remove the AVX2 definition from `UnityImageEncoding.Native/CMakeLists.txt`.

If you are compiling using MSVC, you may also need to apply `MSVC_Fixes.patch` to `UnityImageEncoding.Native/src/lib/etcpak`.

Compile for the platforms you will be using cmake and MSVC or GCC/Clang. If compiling with Clang ensure you are using a modern compiler (e.g. clang++-8 or above).

**Linux:**
```
mkdir -p UnityImageEncoding.Native/out/build/x64-linux && \
cd UnityImageEncoding.Native/out/build/x64-linux && \
cmake ../../../ && \
make -j4
```

**Windows (from "x64 Native Tools Command Prompt for VS 2022"):**
```ps
mkdir UnityImageEncoding.Native/out/build/x64-release 
cd UnityImageEncoding.Native/out/build/x64-release
cmake -G "Ninja" -DCMAKE_C_COMPILER:STRING="cl.exe" -DCMAKE_CXX_COMPILER:STRING="cl.exe" -DCMAKE_BUILD_TYPE:STRING="Release" -DCMAKE_INSTALL_PREFIX:PATH="."  -DCMAKE_MAKE_PROGRAM="C:\PROGRAM FILES\MICROSOFT VISUAL STUDIO\2022\ENTERPRISE\COMMON7\IDE\COMMONEXTENSIONS\MICROSOFT\CMAKE\Ninja\ninja.exe" "../../../"
ninja.exe
```

### Generating Bindings
Edit `BindingsGenerator/Program.cs` with the name/namespace of your project, and comment out platforms you do not wish to build for. Then build and run the program. The bindings will be created in `MyProgram/Native/Windows64` and `MyProgram/Native/Linux64`, and the native libraries will also be copied.

Use a preprocessor directive to specify at build time which bindings to use for your platform:
```cs
#if Windows
using ETCEncodingDemo.Native.Win64;
#else
using ETCEncodingDemo.Native.Linux64;
#endif
```

These directives can be automatically set based on build platform (see [ETCEncodingDemo.csproj](https://github.com/rayshift/unity-image-encoding/blob/master/ETCEncodingDemo/ETCEncodingDemo.csproj)). If you are building on windows and running on linux, you will need to pursue an alternative solution.

### Usage
An example library based on SixLabors.ImageSharp is included at [ETCEncoder.cs](https://github.com/rayshift/unity-image-encoding/blob/master/ETCEncodingDemo/ETCEncoder.cs). Image inputs into the native library must be a byte array with type Bgra32 (1 byte colours ordered Blue-green-red-alpha).

If you are supplying user input, you should ensure that the width and height are accurate, or you may run into issues.
