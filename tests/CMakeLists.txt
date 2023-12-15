######################################
#      BUILD FOR TESTING MODULE
######################################

if(BUILD_TESTS)

    ## vcpkg libraries - Logging header
    # Required by vckpge
    find_package(glog CONFIG REQUIRED)
    #--------------------------------------------------
    #               LINK THE FILES IN THE BUILD
    #                  (Source files)
    #--------------------------------------------------
    set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # To genereate the `commpile_commands.json` file
    # This will read all the files inside our tests module
    file(GLOB_RECURSE SOURCES ./*.cpp            # For define all curernt tests/*.cpp
                              ../src/lib/*.cpp   # For define all the source files excpet main.cpp
    )
    # Remove main.cpp from the list
    # list(REMOVE_ITEM SOURCES "${CMAKE_SOURCE_DIR}/src/main.cpp") # Not Working!!
    add_executable(my_test ${SOURCES}) # ../src/lib/veclib/lib/vector2d.cpp ../src/lib/veclib/lib/vect.cpp

    #--------------------------------------------------
    #               TESTED SOURCE FILES
    #--------------------------------------------------
    # We have included here the called tested code inside the src
    # Which we replace the need to write //#include "../src/lib/veclib/include/vector2d.h"
    # instead we use (#include "vector2d.h") in the my_test1.cpp module for example.

   include_directories("../src/lib/veclib/include/")
    #--------------------------------------------------
    #               LINK OUTSIDE SOURCE FILES
    #                 (external libraries)
    #--------------------------------------------------
    # Now, we link the external libraries that out of the source
  # Link headers
  target_include_directories(
    my_test PRIVATE
            glog::glog
            GTest::gtest_main

    )

  target_link_libraries(
    my_test
    PRIVATE
            glog::glog
            GTest::gtest_main

    )
    include(GoogleTest)
    gtest_discover_tests(my_test)

    # --------------------------------------------------------------------
    #                  Define A Build Type (Test)
    # --------------------------------------------------------------------
    set(CMAKE_BUILD_TYPE Test CACHE STRING "Set the build type to Test" FORCE)
    # Define flags for Test build
    set(CMAKE_CXX_FLAGS_TEST "${CMAKE_CXX_FLAGS_TEST} -Wall -Wextra -g")
    set(CMAKE_C_FLAGS_TEST "${CMAKE_C_FLAGS_TEST} -Wall -Wextra -g")
    # Check if we are using the Test build
    if(CMAKE_BUILD_TYPE STREQUAL "Test")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_TEST}")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${CMAKE_C_FLAGS_TEST}")
    endif()


endif()
