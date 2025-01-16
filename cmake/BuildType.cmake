set(default_build_type "Release")

if(NOT CMAKE_BUILD_TYPE)
    message(STATUS "Seting build type to '${default_build_type}'")
    set(CMAKE_BUILD_TYPE ${default_build_type} CACHE STRING "Choose the type of build." FORCE)
endif()
