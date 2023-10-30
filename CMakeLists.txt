cmake_minimum_required(VERSION 3.5)
project(CPPP_APIs CXX)
#set(SOURCES src/main.cpp src/lib/Employee.cpp)
set(SOURCES src/main.cpp)

# Set the build type if not provided
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE
      "Debug"
      CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
endif()

# Setting my compiling command for clangd language server
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set the output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY
    ${CMAKE_SOURCE_DIR}/build/${CMAKE_BUILD_TYPE})

# Set compiler flags
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ************************************************
# This is the executable for our current project.
# ************************************************
# Set compiler flags
set(CMAKE_CXX_FLAGS_DEBUG
    "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wextra -fcolor-diagnostics -g")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")

# ************************************************
# Can replace the one below
# ************************************************
add_executable(main ${SOURCES})
# Can be equivalent to the below as well, # Apply compiler flags to the specific
# target target_compile_options(main PRIVATE $<$<CONFIG:Debug>:-Wall -Wextra -g>
# $<$<CONFIG:Release>:-O3> )
