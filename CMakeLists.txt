cmake_minimum_required(VERSION 3.11)

project(ringbuffer VERSION 1.0 LANGUAGES CXX)

set(TARGET_NAME ringbuffer_test)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release"
      CACHE STRING "Build type: Release, Debug, MinSizeRel or RelWithDebInfo"
            FORCE)
endif()

add_executable(${TARGET_NAME} src/test.cpp)

target_include_directories(${TARGET_NAME} PRIVATE include)

target_compile_features(${TARGET_NAME} PRIVATE cxx_std_17)

enable_testing()


add_test(simple_test ${TARGET_NAME})
