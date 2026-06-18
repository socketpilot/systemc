# SystemC Installation-Execution

This repository uses **SystemC 3.0.2**, the Accellera reference implementation of the SystemC standard for system-level modeling, simulation, and hardware/software co-design. SystemC extends C++ with constructs for concurrent processes, communication channels, event-driven simulation, and transaction-level modeling (TLM), enabling the development and verification of complex digital systems.

The SystemC library is integrated as an external dependency and is built using CMake and Microsoft Visual Studio on Windows platforms. The project targets a 64-bit architecture and is configured to use the C++17 standard. The generated libraries and headers are used to compile and simulate SystemC-based models within the project environment.

Development and validation were performed using **SystemC 3.0.2**, **CMake 4.x**, and **Microsoft Visual Studio 2026 Community Edition**. Multiple MSVC toolsets are available in the development environment to ensure compatibility with SystemC and other third-party dependencies.

The build process generates both **Debug** and **Release** configurations, allowing developers to perform functional debugging, waveform generation, and performance-oriented simulation runs. Installed artifacts include the SystemC runtime libraries, public header files, and associated build metadata required for downstream applications.

SystemC provides the foundation for:

* Event-driven simulation
* Hardware behavioral modeling
* Register-transfer level (RTL) abstraction
* Transaction-Level Modeling (TLM 2.0)
* Virtual platform development
* Hardware/software co-verification
* Architectural exploration and performance analysis

For additional information regarding the SystemC standard and reference implementation, refer to the official Accellera documentation and release notes corresponding to SystemC 3.0.2.
