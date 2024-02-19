#set(SOURCES src/main.cpp src/lib/Employee.cpp)
#set(SOURCES src/main.cpp)
file(GLOB_RECURSE SOURCES ./*.cpp)

# This will allow the src directory to include the (concepts) directory, or any subdirectory if they have similar to /CPP_APIs/src/concepts/CMakeLists.txt
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# Set the build type if not provided
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE
    "Debug"
    CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
endif()

## vcpkg libraries - Logging header
find_package(glog CONFIG REQUIRED)

# Setting my compiling command for clangd language server
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set the output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY
  ${CMAKE_SOURCE_DIR}/build/${CMAKE_BUILD_TYPE})

# ************************************************
# Can replace the one below
# ************************************************
add_executable(main ${SOURCES})
# Can be equivalent to the below as well, # Apply compiler flags to the specific
# target target_compile_options(main PRIVATE $<$<CONFIG:Debug>:-Wall -Wextra -g>
# $<$<CONFIG:Release>:-O3> )

# -----------------------------
# Will allow emacs to run the `Makefile` options
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
# -----------------------------


#--------------------------------------------------
#               LINK OUTSIDE SOURCE FILES
#                 (external libraries)
#--------------------------------------------------
# Now, we link the external libraries that out of the source
# Link headers
target_include_directories(
  main PRIVATE glog::glog
  )

target_link_libraries(
  main PRIVATE glog::glog
  )



# ************************************************
# This is the executable for our current project.
# ************************************************
# Set compiler flags
# You can add (-Werror, -Wc++11-extensions), However, this will make the compiler more restrictive.
#set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wextra -fcolor-diagnostics -g -Wunused-variable")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wextra  -g -Wunused-variable")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")
