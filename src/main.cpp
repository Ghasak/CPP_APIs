#include "concepts/mylogging.hpp"
#include "concepts/variables.hpp"
// #include <cstddef> // this for reading environment variables
#include <glog/logging.h>
#include <iostream>
#include <iterator>
#include <math.h>
#include <ostream>

int main(int argc, char* argv[]) {
    // Initialize logging
    init_logging(argv);

    std::cout << "(((((((( STARTING WITH VARIABLES TIPS AND HINTS  ))))))))" << std::endl;

    const char* my_char = "This is just a test";
    std::cout << my_char << std::endl;

    for (size_t i = 0; i < 10; i++) {
        LOG(INFO) << i;
        LOG(WARNING) << i;
        LOG(ERROR) << i;
    }
}
