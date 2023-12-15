# Adapted from https://cliutils.gitlab.io/modern-cmake/chapters/projects/submodule.html
# This will recursively download and update the submodules that you ahve in the dependencies.
# All submodules should be included there using (git submodule add <repo_name> dependencies/repo_name)
find_package(Git QUIET)
# Check if git is available in the running system
if(GIT_FOUND)
    # Check if we want to update the submodules (you can turn-off using OFF)
    option(UPDATE_SUBMODULES "Check submodules during build" ON)
    if(NOT UPDATE_SUBMODULES)
        return()
    endif()
    # List the avaialbe submodules
    execute_process(COMMAND ${GIT_EXECUTABLE} submodule
                    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                    OUTPUT_VARIABLE EXISTING_SUBMODULES
                    RESULT_VARIABLE RETURN_CODE
                    OUTPUT_STRIP_TRAILING_WHITESPACE)
    # Update the submodules
    message(STATUS "Updating git submodules:\n${EXISTING_SUBMODULES}")
    execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                    RESULT_VARIABLE RETURN_CODE)
    if(NOT RETURN_CODE EQUAL "0")
        message(WARNING "Cannot update submodules. Git command failed with ${RETURN_CODE}")
        return()
    endif()
    message(STATUS "Git submodules updated successfully")
endif()
