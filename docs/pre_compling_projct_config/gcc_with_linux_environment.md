## Requirements for developers

Your C++ project is compiled using GCC 13.3.0, which links against the C++
standard library libstdc++.so.6. The version of libstdc++.so.6 you need is
located in /usr/lib/x86_64-linux-gnu, and it includes the GLIBCXX_3.4.32 symbol
required by your program.

The error message you encountered indicates that your compiled binary is trying
to link against a version of `libstdc++.so.6` that requires a specific version
of `GLIBCXX` (specifically `GLIBCXX_3.4.32`), which is not available in the
version of `libstdc++.so.6` found in your `Anaconda` environment. This can
happen when there is a mismatch between the version of the C++ standard library
that your code was compiled with and the one available at runtime.

### Steps to Resolve the Issue:

#### 1. **Check and Update GCC and GLIBCXX:**

Ensure that the system's `libstdc++` version is up to date and compatible with
the version of GCC you are using.

1. **Check the current GCC version:**

   `bash g++ --version `

   Ensure it's 13.3.0, as mentioned in the log.

2. **Check the available `GLIBCXX` versions:** `bash strings
/usr/lib/x86_64-linux-gnu/libstdc++.so.6 | grep GLIBCXX ` Ensure that
   `GLIBCXX_3.4.32` is listed.

If it's not listed, you may need to update your system’s `libstdc++`. However,
on Ubuntu, this should generally be up-to-date with the corresponding GCC
version.

#### 2. **Use the System `libstdc++` Library:**

To avoid the conflict with Anaconda’s version of `libstdc++`, you can force
your project to use the system’s `libstdc++` instead of the one provided by
Anaconda.

1. **Deactivate the Anaconda environment:**

   `bash conda deactivate `

2. **Rebuild your project:**

   ````bash cd /home/mdotgh/Desktop/devcode/cpphub/CPP_APIs mkdir -p build/debug
   cd build/debug cmake -G Ninja .. ninja ```

   ````

3. **Run your executable directly, ensuring it uses the system libraries:**
   `bash ./main `

#### 3. **Set the `LD_LIBRARY_PATH`:**

If you need to run your project while the Anaconda environment is activated,
you can explicitly set the `LD_LIBRARY_PATH` to prefer the system’s
`libstdc++`:

```bash export LD_LIBRARY_PATH=/usr/lib/x86_64-linux-gnu:$LD_LIBRARY_PATH
./build/debug/main
```

This ensures that the correct version of `libstdc++` is used during runtime.

#### 4. **Remove the Conflicting Anaconda Library Path:**

You can also temporarily remove the Anaconda library path from your environment
to prevent it from being used:

`bash unset LD_LIBRARY_PATH ./build/debug/main `

Or, temporarily modify it:

`bash LD_LIBRARY_PATH=/usr/lib/x86_64-linux-gnu ./build/debug/main `

### Conclusion

The error you're facing is due to a mismatch between the `libstdc++` version
that your application expects and the one available in the Anaconda
environment. By either deactivating the Anaconda environment, setting the
`LD_LIBRARY_PATH`, or updating the system libraries, you should be able to
resolve the issue and run your compiled C++ application successfully.

The error you are seeing occurs because the version of `libstdc++.so.6` in your
Anaconda environment doesn't include the required `GLIBCXX_3.4.32` symbol,
which your application is trying to use.

Here’s how you can resolve this issue:

### Option 1: Temporarily Adjust `LD_LIBRARY_PATH`

You can adjust the `LD_LIBRARY_PATH` to prioritize the system’s version of
`libstdc++` over the one provided by Anaconda. This way, when your application
runs, it will use the system’s `libstdc++.so.6` instead of Anaconda’s.

1. **Unset the Anaconda library path** or **prepend the system library path**:

   ` bash export LD_LIBRARY_PATH=/usr/lib/x86_64-linux-gnu:$LD_LIBRARY_PATH`

2. **Run your executable**: `bash ./build/debug/main `

This should ensure that your application uses the correct `libstdc++`.

### Option 2: Permanently Adjust the Build Environment

If you often encounter this issue when developing in this environment, you can
either deactivate Anaconda when working on C++ projects or modify your CMake
configuration to use the correct libraries.

1. **Deactivate the Anaconda environment before building**:

   `bash conda deactivate `

2. **Rebuild your project**:

   ````bash cd /home/mdotgh/Desktop/devcode/cpphub/CPP_APIs/build/debug ninja
   clean cmake -G Ninja .. ninja ```

   ````

3. **Run your executable**: `bash ./build/debug/main `

### Option 3: Modify the `CMakeLists.txt` to Prefer System Libraries

Modify your `CMakeLists.txt` to prefer the system's libraries:

1. **Update `CMakeLists.txt`** to explicitly specify the standard library path:

   Add the following line:

   `cmake set(CMAKE_EXE_LINKER_FLAGS "-L/usr/lib/x86_64-linux-gnu") `

2. **Rebuild your project**:

   ````bash cd /home/mdotgh/Desktop/devcode/cpphub/CPP_APIs/build/debug cmake -G
   Ninja .. ninja ```

   ````

3. **Run your executable**: `bash ./build/debug/main `

### Conclusion

By adjusting the `LD_LIBRARY_PATH`, deactivating the Anaconda environment, or
modifying the `CMakeLists.txt`, you should be able to resolve the issue where
your application tries to use the wrong version of `libstdc++.so.6`. This
ensures that the correct version of the C++ standard library is used, and your
application runs without encountering the `GLIBCXX_3.4.32` not found error.

### Understanding `LD_LIBRARY_PATH`

The `LD_LIBRARY_PATH` environment variable is used in Unix-like operating
systems to specify a list of directories where the system should look for
dynamic libraries (.so files) before searching the standard system directories.
It's particularly useful when you have multiple versions of a library and need
to prioritize one over the others, or when libraries are located in
non-standard directories.

### Detailed Breakdown of the Command

`bash export LD_LIBRARY_PATH=/usr/lib/x86_64-linux-gnu:$LD_LIBRARY_PATH `

This command sets the `LD_LIBRARY_PATH` to include the
`/usr/lib/x86_64-linux-gnu` directory, followed by the existing paths in
`LD_LIBRARY_PATH` (if any).

- **`/usr/lib/x86_64-linux-gnu`**: This is a standard directory on Debian-based
  systems (like Ubuntu) where many system libraries, including the standard C++
  library (`libstdc++.so.6`), are stored.
- **`$LD_LIBRARY_PATH`**: This represents the current value of the
  `LD_LIBRARY_PATH` environment variable. By appending this at the end, the
  command ensures that any existing paths are preserved and that the system looks
  in the `/usr/lib/x86_64-linux-gnu` directory first.

### Why Is It Needed to Run Your Project?

The error message you encountered indicates that your program is trying to use
a specific version of the C++ standard library (`libstdc++.so.6`) that requires
the `GLIBCXX_3.4.32` symbol, but it cannot find this symbol in the version of
`libstdc++.so.6` that is being used.

Here's why this happens:

1. **Multiple Versions of `libstdc++.so.6`**:

   - You have a version of `libstdc++.so.6` in your Anaconda environment that
     does not include the `GLIBCXX_3.4.32` symbol.
   - Your project was compiled with GCC 13.3.0, which expects a more recent
     version of `libstdc++.so.6` that includes `GLIBCXX_3.4.32`.

2. **Library Search Path**:

   - When you run your program, the system searches for the required libraries
     (`libstdc++.so.6` in this case) in the directories specified in
     `LD_LIBRARY_PATH`, followed by the standard library directories.
   - If `LD_LIBRARY_PATH` includes Anaconda's directories first, the program
     might use the older, incompatible `libstdc++.so.6` from Anaconda, leading to
     the error.

3. **Solution**:
   - By setting `LD_LIBRARY_PATH` to include `/usr/lib/x86_64-linux-gnu` at the
     start, you ensure that the system's standard `libstdc++.so.6`, which
     includes the required `GLIBCXX_3.4.32` symbol, is used instead of the one
     from Anaconda.

### How Is It Related to Your Project?

- **C++ Standard Library (`libstdc++.so.6`)**:

  - Your C++ project is compiled using GCC 13.3.0, which links against the C++
    standard library `libstdc++.so.6`.
  - The version of `libstdc++.so.6` you need is located in
    `/usr/lib/x86_64-linux-gnu`, and it includes the `GLIBCXX_3.4.32` symbol
    required by your program.

- **Conflict with Anaconda**:
  - The Anaconda environment includes its own version of `libstdc++.so.6`,
    which is older or incompatible with your project. If the system finds this
    version first (because it’s in `LD_LIBRARY_PATH`), your program will fail to
    run due to missing symbols like `GLIBCXX_3.4.32`.

### Which Library Needs It?

- The specific library that needs this adjustment is `libstdc++.so.6`, the GNU
  Standard C++ Library. It is a critical library required by all C++ applications
  for standard C++ functionality.

- Your project specifically needs the version of `libstdc++.so.6` that is
  compatible with the GCC version you used for compilation (GCC 13.3.0). This
  version provides the necessary symbols (e.g., `GLIBCXX_3.4.32`) that your
  compiled binary expects to find at runtime.

### Summary

In summary, by setting `LD_LIBRARY_PATH` to prioritize the system's library
directory (`/usr/lib/x86_64-linux-gnu`), you ensure that the correct version of
`libstdc++.so.6` is used when running your project. This resolves the issue of
missing symbols that arise from an incompatible version of `libstdc++.so.6`
being provided by your Anaconda environment.

In the context of software development, the term "links against" refers to the
process where a program is connected to external libraries during the
compilation or linking phase. This means that the program depends on these
libraries to function correctly. The phrase "links against" is commonly used to
describe how a program uses specific external libraries or resources.

### Nearest Word in Arabic

The nearest word in Arabic to convey this meaning would be **"يرتبط بـ"** or
**""**. These phrases suggest a dependency or connection to something external,
which is similar to what "links against" means in this context.

### Translation to Arabic

The sentence "Your C++ project is compiled using GCC 13.3.0, which links
against the C++ standard library `libstdc++.so.6`." can be translated to Arabic
as:

**"يتم تجميع مشروع C++ الخاص بك باستخدام GCC 13.3.0، والذي يرتبط بمكتبة C++
القياسية `libstdc++.so.6`."**

This translation preserves the meaning that the C++ project relies on the C++ standard library during the compilation process.
