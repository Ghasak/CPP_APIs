#include <glog/logging.h>
#include "concepts/features/timing.hpp"
#include "concepts/mylogging.hpp"
#include <chrono>
#include <thread>
#include <algorithm>
#include <iostream>

void timing_concept() {
    // basic_timing_with_chrone();

    tested_function_performance();
}

void basic_timing_with_chrone() {
    using namespace std::literals::chrono_literals;          // needed for the sleep_for
    auto start = std::chrono::high_resolution_clock::now();  // start time
    std::this_thread::sleep_for(10s);                        // pause execution for 1 sec.
    auto end = std::chrono::high_resolution_clock::now();    // start time
    std::chrono::duration<float> duration = end - start;

    LOG(INFO) << RED << "Current time -> " << YELLOW << duration.count() << "s " << RESET;
}

Timer::Timer() { start = std::chrono::high_resolution_clock::now(); }
Timer::~Timer() {
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    float ms = duration.count() * 1000.0f;
    std::cout << BLUE << "Timer took " << YELLOW << ms << MAGENTA << " ms" << std::endl;
}

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
