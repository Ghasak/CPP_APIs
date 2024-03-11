# Concepts in python vs C++

<!-- markdown-toc start - Don't edit this section. Run M-x markdown-toc-refresh-toc -->
**Table of Contents**

- [Concepts in python vs C++](#concepts-in-python-vs-c)
    - [Concepts](#concepts)
    - [Decorators in Python and Equalvient concept in C++](#decorators-in-python-and-equalvient-concept-in-c)
    - [Example -1-](#example--1-)
        - [In python we write](#in-python-we-write)

<!-- markdown-toc end -->

## Concepts

In this section, we will discuss the most commonly used similarities between
different things in Python that I frequently utilize and compare to what I am
currently implementing in C++.


## Decorators in Python and Equalvient concept in C++

In Python, a decorator is a function that takes another function as its input
and returns a modified version of it. Decorators are used to add functionality
to existing functions without modifying the original code. This feature is not
present in C++, but there is an equivalent concept called "function wrapping".

In C++, a function wrapper is a function that takes another function as its
argument and returns a modified version of it. The main difference between
decorators in Python and function wrappers in C++ is the syntax used to define
them.

Here's an example of how you can implement a simple function wrapper in C++:

```cpp
#include <iostream>

// Define the function wrapper that takes another function as input and returns a modified version of it
template<typename Fn>
auto wrap(Fn func) {
  return [=](int x) {
    std::cout << "Inside wrapper: ";
    int result = func(x); // Call the original function with the same argument
    std::cout << "Returning from wrapper: " << result;
    return result;
  };
}

// Define a simple function to be wrapped
int add(int x) {
  std::cout << "Inside add(): ";
  int result = x + 10; // Perform some computation and return the result
  std::cout << "Returning from add(): " << result;
  return result;
}

// Call the wrapped function with the same argument as the original function
int main() {
  auto wrapped_add = wrap(add); // Wrap the 'add' function using our wrapper function
  int result = wrapped_add(20); // Call the wrapped function with the same argument as before
  std::cout << "Returning from main(): " << result;
  return 0;
}
```

In this example, we define a simple `add` function that takes an integer and
returns its sum after adding 10 to it. We then define a function wrapper called
`wrap` that takes another function as input (in our case, `add`) and returns a
modified version of it. The wrapper function adds some logging statements around
the call to the original function and returns the result.

Finally, we call the wrapped function with the same argument as before and print
the result. This should output:

```sh
Inside add(): 20
Inside wrapper: Inside add(): 30
Returning from wrapper: 40
Returning from main(): 40
```

Note that in this example, we used a lambda function inside the `wrap` function
to create a modified version of the original function. This is called "function
capture" and allows us to access the inputs (variables) of the wrapped function
inside our wrapper function.

In Python, you can define decorators using the `@decorator` syntax to wrap an
existing function without needing to call a separate wrapper function
explicitly. This feature is not available in C++, but the equivalent
functionality can be achieved using lambda functions or function objects as
arguments to higher-order functions like `std::bind`, `std::function`, and
`std::mem_fn`.

In summary, while Python's decorators and C++'s function wrapping serve similar
purposes of adding functionality to existing functions without modifying the
original code, they have different syntaxes and implementations due to the
differences in their programming paradigms.


## Example -1-
### In python we write

```python

def timer(func):  # This is our decorator function
    def wrapper():  # A new function created by the decorator
        start_time = time.time()

        func()  # Calling the original function

        end_time = time.time()
        execution_time = end_time - start_time

        print(f"Function took {execution_time} seconds to execute")
    return wrapper

```

- Then we wrap our function with this decorator
```python
@timer
def my_function():
    for i in range(10):  # Do some time-consuming task here
        pass
```

Similary to implement this in C++ we can use *we use function pointer concept*:

```cpp
#include <iostream>
using namespace std;

class Timer {
public:
    void operator()(void) const {
        auto start_time = clock();

        // Function to be timed

        auto end_time = clock();
        float execution_time = (end_time - start_time);
        cout << "Function took " << execution_time << " seconds to execute" << endl;
    }
};

int main() {
    Timer timer;

    // Decorate the function with a functor
    auto my_function = [&](){timer();};
    my_function();
}

```
