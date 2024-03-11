#include <gflags/gflags_declare.h>
#include <cstddef>
#include "concepts/mylogging.hpp"
#include <memory>

#pragma once

void tracking_memory_allocation_concpet();

void* operator new(size_t);
void operator delete(void*, size_t) noexcept;

/*
 *  Struct used for testing with memory allocation and tracking memory
 */
struct Object {
    int x, y, z;
    bool verbose_message;
    Object(int, int, int, bool);
    ~Object();
};

/*
 * This struct will be used a tracker for the memory in bytes
 * which will be used as a metric for our checking and
 * performance improvement
 */
struct AllocationMetrics {
    uint32_t TotalAllocated = 0;
    uint32_t TotalFreed = 0;
    uint32_t CurrentUsage();
};

void PrintMemoryUsage();
