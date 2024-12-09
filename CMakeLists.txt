cmake_minimum_required(VERSION 3.11)

project(ringbuffer VERSION 1.0 LANGUAGES CXX)

add_compile_options(-Wall -Wextra -Wpedantic -Wno-c++17-extensions)

find_package(Threads REQUIRED)

add_executable(ringbuffer_test src/test.cpp)

target_link_libraries(ringbuffer_test Threads::Threads)

target_compile_features(ringbuffer_test PRIVATE cxx_std_17)

target_include_directories(ringbuffer_test PRIVATE include)

enable_testing()

add_test(ringbuffer_test ringbuffer_test)
