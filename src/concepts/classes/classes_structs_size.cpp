#include "concepts/mylogging.hpp"
#include <glog/logging.h>
#include "concepts/classes/classes_structs_size.hpp"
#include <cstring>
#include <string>

void classes_size_concept() {
    // Primitive Class data type Measure the size
    const char* my_name = "ABC";
    LOG(INFO) << RED "Size of this char* pointer data type -> " << BLUE << sizeof(my_name) << BLUE
              << "with lenghth" << strlen(my_name) << RESET;
    Vec2d v1 = Vec2d(10, 20, "ABC");
    LOG(INFO) << RED "Size of this Vec2d Class data type -> " << BLUE << sizeof(Vec2d) << RESET;
    LOG(INFO) << BLUE << "WE HAVE x, y both int of              4-bytes size" << RESET;
    LOG(INFO) << BLUE << "WE HAVE char* pointer which is int of 8-bytes size" << RESET;
    LOG(INFO) << YELLOW << "------------------------------------------------" << RESET;
    LOG(INFO) << MAGENTA << "SUM of two integers 2* 4-bytes + 1 pointer int of 8-bytes = 16 Bytes"
              << RESET;

    // Class with STD c++ data structure
    std::string my_string_input = "Hello Complex Class";
    Vec2c v2 = Vec2c(10, 20, my_string_input);
    LOG(INFO) << RED "Size of this Vec2c Class data type -> " << BLUE << sizeof(Vec2c) << RESET;
    LOG(INFO) << BLUE << "WE HAVE x, y both int of              4-bytes size" << RESET;
    LOG(INFO) << BLUE << "WE HAVE string which is has inner-data for capacity, length and pointer"
              << RESET;
    LOG(INFO) << BLUE
              << "Both Capacity and length and the pointer for heap allocating this string are "
                 "8-bytes length"
              << RESET;
    LOG(INFO) << YELLOW << "------------------------------------------------" << RESET;
    LOG(INFO) << MAGENTA << "SUM of 3 int of 8-bytes = 24 Bytes" << RESET;
    LOG(INFO) << MAGENTA
              << "There is also padding and alignment (reservation for expanding the string)"
              << RESET;
    LOG(INFO) << YELLOW << "It seems this padding/alignment is about -> " << RED << "8-bytes"
              << RESET;
}

// Class with Primitive types
Vec2d::Vec2d(int xi, int yi, const char* ci)
    : x{xi},
      y{yi},
      c{ci} {}

Vec2d::~Vec2d() { LOG(INFO) << RED << "Class [Vec2d] Object got destroyed" << RESET; }

// Class with STD c++ data structure
Vec2c::Vec2c(int xi, int yi, const std::string& name)
    : X{xi},
      Y{yi},
      m_Name{name} {}

Vec2c::~Vec2c() { LOG(INFO) << RED << "Class [Vec2c] Object got destroyed" << RESET; }
