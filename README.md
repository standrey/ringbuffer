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
