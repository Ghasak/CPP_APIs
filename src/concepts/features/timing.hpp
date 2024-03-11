#pragma once
#include <chrono>

/*
 * Adding here a timing for checking the performance of a given code-block
 * It is part of our Bench-marking in C++
 */
void timing_concept();
void basic_timing_with_chrone();

struct Timer {
    std::chrono::time_point<std::chrono::steady_clock> start, end;
    std::chrono::duration<float> duration;

    Timer();
    ~Timer();
};

void tested_function_performance();
