# Track Memory Allocations

The easy way to track the memory allocation in C++. Lets dive deep into this
concept. The idea is that we can create a metric to track all our memeory
allocation on the heap by altering the implementation of the `new` and `delete`
operators.

## Concept

We will track the `new` operator globally using,The implementation is listed in
the module `features` at "src/concepts/features/track_memory_allocation.cpp".

```cpp

/*
 * We alter the new operator here as we will use it to track
 * the memory that we allocate on the heap
 */
void* operator new(size_t size) {
    if (verbose) {
        std::cout << BLUE << "Allocating " << YELLOW << size << " Bytes" << RESET << "\n";
    }
    return malloc(size);
}

/*
 * Altering the delete keyword which is also used to track our
 * de-allocations so that we can use it for our checking
 */
void operator delete(void* memory, size_t size) noexcept {
    if (verbose) {
        std::cout << BLUE << "De-Allocating " << YELLOW << size << " Bytes" << RESET << "\n";
    }

    free(memory);
}



int main(int argc, char* argv[]){
    Object* obj = new Object(3, 2, 4);
    delete obj;
}

```

## Passing Size fo the object to the delete
I have found that for different complier we would have a different
implementation. For example:

```cpp

/*
 * Altering the delete keyword which is also used to track our
 * de-allocations so that we can use it for our checking
 */

static bool verbose = false;
void operator delete(void* memory, size_t size) {
    if (verbose) {
        std::cout << BLUE << "De-Allocating " << YELLOW << size << " Bytes" << RESET << "\n";
    }

    free(memory);
}

```

In order to pass the size to the customed delete operator we need to conisder which complier we are using:
The configurations that we needed are all included in the class related to the `memory tracking`.

- `MSVC`: complier by micorsoft offers this by default
- `GCC` : same
- `clang`: You will need to pass `-fsized-deallocation` to make it works.
