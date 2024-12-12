cmake_minimum_required(VERSION 3.11)

project(ringbuffer VERSION 1.0 LANGUAGES CXX)

add_executable(ringbuffer_test src/test.cpp)

target_include_directories(ringbuffer_test PRIVATE include)

set(COMPILE_OPTIONS "-m64;-fPIC;-fno-strict-aliasing;-Wall;-Wextra;-Wpedantic;-Wno-multichar;-Wno-comment;-Wno-sign-compare;-funsigned-char;-pthread;-Wno-deprecated;-Wno-reorder;-ftemplate-depth-64;-fno-gnu-keywords;-std=c++17;-Winline")

set(COMPILE_DEBUG_OPTIONS "${COMPILE_OPTIONS};-fsanitize=thread;-O2")

set(COMPILE_RELEASE_OPTIONS "${COMPILE_OPTIONS};-O3")

target_compile_options(ringbuffer_test PRIVATE "$<$<CONFIG:Debug>:${_COMPILE_DEBUG_OPTIONS}>")

target_compile_options(ringbuffer_test PRIVATE "$<$<CONFIG:Release>:${COMPILE_RELEASE_OPTIONS}>")

enable_testing()

add_test(ringbuffer_test ringbuffer_test)
