#[[
    Adding here a minimum requirements for using the CMake
     # cmake_minimum_required(VERSION ";%s" )
]]

cmake_minimum_required(VERSION "3.0")
#[[
    We add to the CMAKE_CXX_FLAGS the -std=c++20 flag
    so it will add it also to the CMAKE_CXX_FLAGS string

]]
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")

project(myProject)
#[[
    Adding here the path to the source files
    # add_subdirectory(src)
]]
add_executable(myProject main.cpp)





