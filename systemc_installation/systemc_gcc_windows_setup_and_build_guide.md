# SystemC + GCC (MinGW) + CMake Setup Guide on Windows

This document provides a complete flow to:
1. Install GCC/MinGW
2. Build and install SystemC
3. Create and build a SystemC project using CMake
4. Run the executable
5. Debug common issues

---

# 1. Prerequisites

Install the following:

- CMake
- MinGW-w64 GCC/G++
- SystemC source package

Verify installation:

```cmd
g++ --version
cmake --version
```

Expected:

```text
g++ (Rev...) 16.x.x
cmake version 3.x
```

Ensure MinGW bin directory is in PATH:

Example:

```text
C:\mingw64\bin
```

Verify:

```cmd
g++ --version
```

---

# 2. Build and Install SystemC

Assume:

```text
D:\Practive_Learning\SystemC\systemc
```

contains SystemC source.

Create build directory:

```cmd
D:
cd D:\Practive_Learning\SystemC\systemc

mkdir build_gcc
cd build_gcc
```

Configure:

```cmd
cmake .. ^
-G "MinGW Makefiles" ^
-DCMAKE_C_COMPILER=gcc ^
-DCMAKE_CXX_COMPILER=g++ ^
-DCMAKE_CXX_STANDARD=17 ^
-DCMAKE_CXX_STANDARD_REQUIRED=ON ^
-DCMAKE_INSTALL_PREFIX=../install_gcc
```

Build:

```cmd
mingw32-make -j4
```

Install:

```cmd
mingw32-make install
```

After installation:

```text
D:\Practive_Learning\SystemC\systemc\install_gcc
```

should contain:

```text
include
lib
share
```

Verify:

```text
D:\Practive_Learning\SystemC\systemc\install_gcc\lib\libsystemc.a
```

exists.

---

# 3. Project Directory Structure

Example:

```text
E:\sample
│
├── main.cpp
├── i2c_controller.cpp
├── i2c_controller.h
├── i2c_registers.cpp
├── i2c_registers.h
├── CMakeLists.txt
│
└── build_gcc
```

Create build directory:

```cmd
mkdir build_gcc
```

---

# 4. CMakeLists.txt

Use:

```cmake
cmake_minimum_required(VERSION 3.16)

project(i2c_project LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_PREFIX_PATH
"D:/Practive_Learning/SystemC/systemc/install_gcc")

find_package(SystemCLanguage CONFIG REQUIRED)

add_executable(i2c_project
    main.cpp
    i2c_controller.cpp
    i2c_registers.cpp
)

target_link_libraries(i2c_project
PRIVATE
SystemC::systemc
)
```

---

# 5. Configure Project

Move into build directory:

```cmd
cd E:\sample\build_gcc
```

Configure:

```cmd
cmake .. ^
-G "MinGW Makefiles" ^
-DCMAKE_C_COMPILER=C:/mingw64/bin/gcc.exe ^
-DCMAKE_CXX_COMPILER=C:/mingw64/bin/g++.exe
```

Expected:

```text
-- The C compiler identification is GNU
-- The CXX compiler identification is GNU
```

Not:

```text
MSVC
Visual Studio
cl.exe
```

---

# 6. Build Project

```cmd
mingw32-make
```

Verbose build:

```cmd
mingw32-make VERBOSE=1
```

Executable generated:

```text
i2c_project.exe
```

---

# 7. Run Executable

In Windows CMD:

```cmd
i2c_project.exe
```

or:

```cmd
.\i2c_project.exe
```

Do NOT use:

```cmd
./i2c_project.exe
```

because that is Linux shell syntax.

---

# 8. Typical Successful Output

```text
SystemC 3.0.2-Accellera
Constructor called
SC_METHOD executed at 10 ns
```

---

# 9. Common Errors and Fixes

## Error:

```text
fatal error: systemc.h: No such file or directory
```

Cause:

SystemC include path missing.

Fix:

Use:

```cmake
find_package(SystemCLanguage CONFIG REQUIRED)
```

and:

```cmake
target_link_libraries(
PRIVATE
SystemC::systemc)
```

---

## Error:

```text
undefined reference to
sc_api_version_3_0_2_cxx201703L
```

Cause:

C++ ABI mismatch or incorrect linkage.

Fix:

Rebuild SystemC using:

```cmd
-DCMAKE_CXX_STANDARD=17
```

and use:

```cmake
find_package(SystemCLanguage CONFIG REQUIRED)
```

instead of manual linking.

---

## CMake Still Uses MSVC

Delete:

```text
CMakeCache.txt
CMakeFiles
```

Then configure again:

```cmd
cmake .. ^
-G "MinGW Makefiles" ^
-DCMAKE_C_COMPILER=gcc ^
-DCMAKE_CXX_COMPILER=g++
```

---

# Final Working Flow

```cmd
mkdir build_gcc
cd build_gcc

cmake .. ^
-G "MinGW Makefiles" ^
-DCMAKE_C_COMPILER=gcc ^
-DCMAKE_CXX_COMPILER=g++

mingw32-make

i2c_project.exe
```

This flow successfully builds and runs SystemC projects using GCC/MinGW and CMake on Windows.

