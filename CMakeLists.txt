cmake_minimum_required(VERSION 3.11)

project(ringbuffer VERSION 1.0 LANGUAGES CXX)

set(TARGET_NAME ringbuffer_test)

include(cmake/BuildType.cmake)

add_executable(${TARGET_NAME} src/test.cpp)

target_include_directories(${TARGET_NAME} PRIVATE include)

target_compile_features(${TARGET_NAME} PRIVATE cxx_std_20)

enable_testing()

add_test(simple_test ${TARGET_NAME})


Include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.4.0 # or a later release
)

FetchContent_MakeAvailable(Catch2)

list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(CTest)
include(Catch)

add_executable(catch2tests tests/test_ringbuffer.cpp)
target_compile_features(catch2tests PRIVATE cxx_std_20)
target_include_directories(catch2tests PRIVATE include)
target_link_libraries(catch2tests PRIVATE Catch2::Catch2WithMain)
catch_discover_tests(catch2tests)

