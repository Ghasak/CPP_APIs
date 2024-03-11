# Timing in CPP

## Concept

Starting with the basics, we can use the standard library `chrono` which covers
up to 99% of all our needs for time with high resolution. We can use this
similar to decoration (timer) that we used in python before.

```cpp

#include <glog/logging.h>
#include "concepts/features/timing.hpp"
#include "concepts/mylogging.hpp"
#include <chrono>
#include <thread>
#include <algorithm>

void timing_concept() {
    using namespace std::literals::chrono_literals;          // needed for the sleep_for
    auto start = std::chrono::high_resolution_clock::now();  // start time
    std::this_thread::sleep_for(10s);                        // pause execution for 1 sec.
    auto end = std::chrono::high_resolution_clock::now();    // start time
    std::chrono::duration<float> duration = end - start;

    LOG(INFO) << RED << "Current time -> " << YELLOW << duration.count() << "s " << RESET;
}
```

## How about a better way to time your activities

Lets create a struct with a constructor to start the timer lets check this

```cpp


struct Timer {
    std::chrono::time_point<std::chrono::steady_clock> start, end;
    std::chrono::duration<float> duration;

    Timer() { start = std::chrono::high_resolution_clock::now(); }
    ~Timer() {
        end = std::chrono::high_resolution_clock::now();
        duration = end - start;
        float ms = duration.count() * 1000.0f;
        std::cout << "Timer took " << ms << "ms " << std::endl;
    }
};

```

Now we can use this with any function that we need to mark the duration, for example :

```cpp

/*
 * We tested the function using the Timer structure we created to evaluate its performance
 * The objective is to measure the function's execution time in milliseconds, which may vary
 * depending on the user's needs Within the scope of the function, the destructor of the Timer
 * structure is called upon exiting, thereby computing the execution duration.
 */
void tested_function_performance() {
    Timer timer;
    for (size_t i = 0; i < 100; i++) {
        if ((i % 10) == 0) {
            LOG(INFO) << RED << "Value if i => " << MAGENTA << i << RESET;
        }
    }
}

int main(int argc, char* argv[]){
    testing _function_performance();

  return 0
}

```
