cmake_minimum_required(VERSION 3.5)
project(YourProjectName CXX)

set(SOURCES src/main.cpp)

# Set the build type if not provided
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
endif()

# Set the output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/${CMAKE_BUILD_TYPE})

# Add the executable target
add_executable(main ${SOURCES})

# Include directories
target_include_directories(main PRIVATE ${CMAKE_SOURCE_DIR}/dependencies/include)

# Link directories
target_link_directories(main PRIVATE ${CMAKE_SOURCE_DIR}/dependencies/lib)

# Link libraries
target_link_libraries(main PRIVATE SDL2)

# Set compiler flags
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wextra -g")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")

