#include <glog/logging.h>
#include "concepts/features/track_memory_allocation.hpp"
#include "concepts/mylogging.hpp"
#include <iostream>
#include <cstdlib>
#include <memory>
#include <string>

static bool s_verbose = false;
static AllocationMetrics s_AllocationMetrics;
static size_t s_CallingPrintingMemoryCount = 0;

void tracking_memory_allocation_concpet() {
    s_verbose = false;
    bool verbose_messge = false;
    //-1- first calling
    PrintMemoryUsage();
    Object* obj = new Object(3, 2, 4, verbose_messge);
    delete obj;

    //-2- second calling
    PrintMemoryUsage();

    {
        std::unique_ptr<Object> my_unique_ptr =
            std::make_unique<Object>(10, 20, 30, verbose_messge);

        //-3- third calling
        PrintMemoryUsage();
    }

    std::string* my_string = new std::string("This is just a string ");

    //-4- forth calling
    PrintMemoryUsage();
    delete my_string;

    s_verbose = false;
}

Object::Object(int x, int y, int z, bool verbose_message)
    : x{x},
      y{y},
      z{z},
      verbose_message{verbose_message} {
    if (verbose_message) {
        std::cout << RED << "Object with " << YELLOW << x << RESET << ", " << YELLOW << y << RESET
                  << ", " << YELLOW << z << RESET << std::endl;
    }
}

Object::~Object() {
    if (verbose_message) {
        std::cout << MAGENTA << "Object got destroyed" << std::endl;
    }
}

/*
 * We alter the new operator here as we will use it to track
 * the memory that we allocate on the heap
 */
void* operator new(size_t size) {
    if (s_verbose) {
        // std::cout << BLUE << "Allocating " << YELLOW << size << " Bytes" << RESET << "\n";
        s_AllocationMetrics.TotalAllocated += size;
    }

    return malloc(size);
}

/*
 * Altering the delete keyword which is also used to track our
 * de-allocations so that we can use it for our checking
 */
void operator delete(void* memory, size_t size) noexcept {
    if (s_verbose) {
        // std::cout << BLUE << "De-Allocating " << YELLOW << size << " Bytes" << RESET << "\n";
        s_AllocationMetrics.TotalFreed += size;
    }

    free(memory);
}

/*
 * Implementation of the memory tracker metric
 * This is based on the strcut AllocationMetrics
 * Here is a function for getting total allocation
 */
uint32_t AllocationMetrics::CurrentUsage() { return this->TotalAllocated - this->TotalFreed; }

void PrintMemoryUsage() {
    s_CallingPrintingMemoryCount += 1;
    std::cout << YELLOW << "Calling num: " << RED << s_CallingPrintingMemoryCount << BLUE
              << " Memory Usage: " << MAGENTA << s_AllocationMetrics.CurrentUsage()
              << RED " Bytes\n";
}
