[![C++ CI](https://github.com/standrey/ringbuffer/workflows/C++%20CI%20on%20github/badge.svg)](https://github.com/standrey/ringbuffer/actions)
[![License](https://img.shields.io/badge/license-MIT-blue.svg)](https://raw.githubusercontent.com/standrey/ringbuffer/master/LICENSE)

A single producer - single consumer wait-free and lock-free fixed size queue written in C++17.
The implementation is just an answer to the pre-technical interview that has been successfully failed.

# Configure the build
cmake -S . -B build/ -D CMAKE_BUILD_TYPE=Debug

# Build the test binary
cmake --build build/

# Configure a release build
cmake -S . -B build/ -D CMAKE_BUILD_TYPE=Release

# Build the release binary
cmake --build build/

# My local CPU information so far 
![mylocalpc](https://github.com/user-attachments/assets/84959587-24c2-47f2-8f19-04a842ce7bb8)

Architecture:             x86_64
  CPU op-mode(s):         32-bit, 64-bit
  Address sizes:          39 bits physical, 48 bits virtual
  Byte Order:             Little Endian
CPU(s):                   16
  On-line CPU(s) list:    0-15
Vendor ID:                GenuineIntel
  Model name:             11th Gen Intel(R) Core(TM) i7-11700K @ 3.60GHz
    CPU family:           6
    Model:                167
    Thread(s) per core:   2
    Core(s) per socket:   8
    Socket(s):            1
    Stepping:             1
