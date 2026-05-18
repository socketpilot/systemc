# SystemC + MSVC Complete Setup Guide

This document explains:
1. Building and installing SystemC using MSVC
2. Creating a SystemC Visual Studio project
3. Building and running a SystemC application
4. Required MSVC-specific settings (/vmg)

---

# Part 1: Build and Install SystemC using MSVC

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

