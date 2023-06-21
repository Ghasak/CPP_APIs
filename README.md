##  Generate Builds
Assume our project is structured as following

```sh
╰─ tree -d -L 4
.
├── build
│   ├── debug
│   │   └── CMakeFiles
│   │       ├── 3.26.3
│   │       ├── CMakeScratch
│   │       ├── main.dir
│   │       └── pkgRedirects
│   └── release
│       └── CMakeFiles
│           ├── 3.26.3
│           ├── main.dir
│           └── pkgRedirects
└── src
```

### Step -1  At root directory
At the root directory (`.`) run the following command in two options

#### Release Mode
```sh
cmake -DCMAKE_BUILD_TYPE=Release -S . -B build/release
```
#### Debug Mode
```sh
cmake -DCMAKE_BUILD_TYPE=Debug -S . -B build/debug
```
### Step -2 make binary
Go to each directory for example `build/release` or `build/debug` and use the command

```sh
make
```
It will genearte the binary at the same directory. See other options using
`make help` (e.g. I use `make clean` to get remove the binary that I built).

## Notes
If I use the following snippet inside my `CmakeList.txt` located at the roort directory. It will also work, but the generated files for the build will be located at the root directory. These files are
- `CMakeFiles` which a directory.
- `cmake_install.cm`
- `CMakeCache.txt`

```sh
# Set the output directory based on the build type
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/build/release)
else()
    set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/build/debug)
endif()
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/build/debug)  # Set the output directory
```

- All these `Cmake` generated output files should not be located at the root
directory that's why I used instead:

```sh
# Set the build type if not provided
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
endif()

# Set the output directories
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/${CMAKE_BUILD_TYPE}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/${CMAKE_BUILD_TYPE}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/${CMAKE_BUILD_TYPE})
```
