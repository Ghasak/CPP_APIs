#include "variables.hpp"
#include "../mylogging.hpp"
#include <iostream>
#include <limits>
#include <glog/logging.h>
#include <iostream>
#include <limits>
#include <algorithm>

void data_type_concept() { void data_type_table(); }

void data_type_table() {
    std::cout << "(((((((( INTEGER (int, int32) VALUE ))))))))" << std::endl;
    LOG(INFO) << "--";
    std::cout << "-------------------------------------------" << std::endl;
    LOG(INFO) << BLUE << "- Number of bytes in an int: -> " << sizeof(int) << " bytes" << RESET;
    LOG(INFO) << BLUE << "- Maximum value for int    : -> " << std::numeric_limits<int>::max()
              << RESET;
    LOG(INFO) << BLUE << "- Minimum value for int    : -> " << std::numeric_limits<int>::min()
              << RESET;
    LOG(INFO) << BLUE << "- Lowest value for int     : -> " << std::numeric_limits<int>::lowest()
              << RESET;
    std::cout << "-------------------------------------------" << std::endl;
    LOG(INFO) << BLUE << "- Number of bytes in an long int: -> " << sizeof(long int) << " bytes"
              << RESET;
    LOG(INFO) << BLUE << "- Maximum value for long int    : -> "
              << std::numeric_limits<long int>::max() << RESET;
    LOG(INFO) << BLUE << "- Minimum value for long int    : -> "
              << std::numeric_limits<long int>::min() << RESET;
    LOG(INFO) << BLUE << "- Lowest value for long int     : -> "
              << std::numeric_limits<long int>::lowest() << RESET;

    std::cout << "-------------------------------------------" << std::endl;
    LOG(INFO) << BLUE << "- Number of bytes in an signed long int: -> " << sizeof(signed long int)
              << " bytes" << RESET;
    LOG(INFO) << BLUE << "- Maximum value for signed long int    : -> "
              << std::numeric_limits<signed long int>::max() << RESET;
    LOG(INFO) << BLUE << "- Minimum value for signed long int    : -> "
              << std::numeric_limits<signed long int>::min() << RESET;
    LOG(INFO) << BLUE << "- Lowest value for signed long int     : -> "
              << std::numeric_limits<signed long int>::lowest() << RESET;

    std::cout << "-------------------------------------------" << std::endl;
    std::cout << "(((((((( Float-point (float, double) VALUE ))))))))" << std::endl;
    LOG(INFO) << BLUE << "- Number of bytes in an float:       -> " << sizeof(float) << " bytes"
              << RESET;
    LOG(INFO) << BLUE << "- Maximum value for float:           -> "
              << std::numeric_limits<float>::max() << RESET;
    LOG(INFO) << BLUE << "- Minimum value for float:           -> "
              << std::numeric_limits<float>::min() << RESET;
    LOG(INFO) << BLUE << "- Lowest value for float:            -> "
              << std::numeric_limits<float>::lowest() << RESET;

    std::cout << "-------------------------------------------" << std::endl;
    LOG(INFO) << BLUE << "- Number of bytes in an double:       -> " << sizeof(double) << " bytes"
              << RESET;
    LOG(INFO) << BLUE << "- Maximum value for double:           -> "
              << std::numeric_limits<double>::max() << RESET;
    LOG(INFO) << BLUE << "- Minimum value for double:           -> "
              << std::numeric_limits<double>::min() << RESET;
    LOG(INFO) << BLUE << "- Lowest value for double:            -> "
              << std::numeric_limits<double>::lowest() << RESET;

    std::cout << "-------------------------------------------" << std::endl;
    LOG(INFO) << BLUE << "- Number of bytes in an long double:       -> " << sizeof(long double)
              << " bytes" << RESET;
    LOG(INFO) << BLUE << "- Maximum value for long double:           -> "
              << std::numeric_limits<long double>::max() << RESET;
    LOG(INFO) << BLUE << "- Minimum value for long double:           -> "
              << std::numeric_limits<long double>::min() << RESET;
    LOG(INFO) << BLUE << "- Lowest value for long double:            -> "
              << std::numeric_limits<long double>::lowest() << RESET;
}
