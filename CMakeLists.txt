cmake_minimum_required(VERSION 3.5)
project(CPP_APIs CXX)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wextra")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")


# Set the output directory based on the build type
#if(CMAKE_BUILD_TYPE STREQUAL "Release")
#    set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/build/release)
#else()
#    set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/build/debug)
#endif()
#set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/build/debug)  # Set the output directory

# Set the build type if not provided
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
endif()

# Set the output directories
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/${CMAKE_BUILD_TYPE}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/${CMAKE_BUILD_TYPE}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/${CMAKE_BUILD_TYPE})



set(SOURCES src/main.cpp)
add_executable(main ${SOURCES})
