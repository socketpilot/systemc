# SystemC + MSVC Complete Setup Guide

This document explains:
1. Building and installing SystemC using MSVC
2. Creating a SystemC Visual Studio project
3. Building and running a SystemC application
4. Required MSVC-specific settings (/vmg)

---

# Part 1a: Build and Install SystemC using MSVC

Open:

x64 Native Tools Command Prompt for VS 2022

Verify tools:

```cmd
cl
cmake --version
```

You should see MSVC compiler information.

Assume SystemC source is located at:

```text
D:\Practive_Learning\SystemC\systemc
```

Create build folder:

```cmd
D:
cd D:\Practive_Learning\SystemC\systemc

mkdir build_msvc
cd build_msvc
```

Configure SystemC:

```cmd
cmake .. ^
-G "Visual Studio 17 2022" ^
-A x64 ^
-DCMAKE_CXX_STANDARD=17 ^
-DCMAKE_INSTALL_PREFIX=../install_msvc
```

Build Release:

```cmd
cmake --build . --config Release
```

Install:

```cmd
cmake --install . --config Release
```

After installation:

```text
D:\Practive_Learning\SystemC\systemc\install_msvc
```

Expected folders:

```text
include
lib
share
```

---
# Part 1b:
# SystemC 3.0.2 Build Notes (Windows / Visual Studio 2026)

## Environment

* OS: Windows
* Visual Studio: Visual Studio 2026 Community
* CMake: 4.3.1
* SystemC Version: 3.0.2
* Source Repository: https://github.com/accellera-official/systemc

## Clone SystemC

```cmd
git clone https://github.com/accellera-official/systemc.git
cd systemc
git checkout 3.0.2
```

## Verify Version

```cmd
git describe --tags
git status
```

Expected output:

```text
3.0.2
HEAD detached at 3.0.2
nothing to commit, working tree clean
```

## Installed MSVC Toolsets

Available toolsets:

```text
14.29.30133
14.42.34433
14.44.35207
14.51.36231
```

## Problem Encountered

During compilation with Visual Studio 2026 (MSVC 14.51):

```text
error C2039: 'opfx': is not a member of 'std::basic_ostream'
error C2039: 'osfx': is not a member of 'std::basic_ostream'
```

File:

```text
src/sysc/datatypes/int/sc_int64_io.cpp
```

Affected lines:

```cpp
os.osfx();
if (os.opfx())
```

The repository was verified as:

```cmd
git describe --tags
```

Output:

```text
3.0.2
```

No local modifications:

```cmd
git status
```

Output:

```text
working tree clean
```

## Recommended Approach

Do not modify SystemC source files.

Instead, build using an older MSVC toolset.

Recommended toolset:

```text
v142 (Visual Studio 2019)
```

## Create a Fresh Build Directory

```cmd
cd C:\SystemC\systemc

mkdir build_v142
cd build_v142
```

## Configure CMake

```cmd
cmake .. ^
-G "Visual Studio 18 2026" ^
-A x64 ^
-T v142 ^
-DCMAKE_CXX_STANDARD=17 ^
-DCMAKE_INSTALL_PREFIX=../install_msvc
```

## Build Debug

```cmd
cmake --build . --config Debug
```

## Build Release

```cmd
cmake --build . --config Release
```

## Install Debug

```cmd
cmake --install . --config Debug
```

## Install Release

```cmd
cmake --install . --config Release
```

## Output Locations

Build output:

```text
build_v142\src\Debug\
build_v142\src\Release\
```

Installation output:

```text
install_msvc\
├── include\
├── lib\
├── bin\
```

## Notes

* Reusing an existing build directory may cause CMake cache conflicts.
* Use a fresh build directory when changing generator, platform, or toolset.
* Verify the compiler version during configuration.
* Preferred compiler version:

```text
MSVC 19.29.xxxxx
```

instead of:

```text
MSVC 19.51.xxxxx
```

when testing compatibility with SystemC 3.0.2.

# Part 2: Create Visual Studio SystemC Project

Open Visual Studio.

Select:

File
→ New
→ Project
→ Empty C++ Project

Choose:

- Platform: x64
- Configuration: Release (or Debug)

Add source files:

```text
main.cpp
i2c_controller.cpp
i2c_controller.h
i2c_registers.cpp
i2c_registers.h
```

---

# Part 3: Configure Project Settings

Open:

Project
→ Properties

Select:

All Configurations
x64

---

## Include path

C/C++
→ General
→ Additional Include Directories

Add:

```text
D:\Practive_Learning\SystemC\systemc\install_msvc\include
```

---

## Library path

Linker
→ General
→ Additional Library Directories

Add:

```text
D:\Practive_Learning\SystemC\systemc\install_msvc\lib
```

---

## Add SystemC library

Linker
→ Input
→ Additional Dependencies

Add:

```text
systemc.lib
```

---

## Set C++ Standard

C/C++
→ Language
→ C++ Language Standard

Select:

```text
ISO C++17 (/std:c++17)
```

---

## Runtime Library

C/C++
→ Code Generation
→ Runtime Library

Release:

```text
Multi-threaded DLL (/MD)
```

Debug:

```text
Multi-threaded Debug DLL (/MDd)
```

Make sure Debug and Release match how SystemC was built.

---

# Critical SystemC Setting

Open:

C/C++
→ Command Line
→ Additional Options

Add:

```text
/VMG
```

(or lowercase /vmg)

This flag is extremely important.

SystemC internally uses member-function pointers for:

- SC_METHOD
- SC_THREAD
- callbacks
- process registration

Without /vmg a manually created Visual Studio project may:

- compile successfully
- link successfully
- crash during execution

Typical crash:

```text
0xC0000005
Access violation
0xFFFFFFFFFFFFFFFF
```

CMake-generated MSVC projects usually add the required behavior automatically, but manual projects may require this setting.

---

# Part 4: Build and Run

Build:

Build
→ Build Solution

or:

Ctrl + Shift + B

Run:

Debug
→ Start Without Debugging

or:

Ctrl + F5

Expected:

```text
SystemC banner
Constructor called
SC_METHOD executed
```

---

# Important Notes

Keep GCC and MSVC installations separate.

Example:

```text
build_gcc
install_gcc

build_msvc
install_msvc
```

Never mix:

- install_gcc with Visual Studio projects
- libsystemc.a with MSVC
- systemc.lib with GCC

Use:

GCC → libsystemc.a
MSVC → systemc.lib

