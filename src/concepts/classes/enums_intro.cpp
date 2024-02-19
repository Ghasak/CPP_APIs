#include "concepts/classes/enums_intro.hpp"
#include "concepts/mylogging.hpp"
#include <glog/logging.h>
#include <iostream>

void enums_concept_hub() {
    // How to use enums
    using_enums();
}

void using_enums() {
    // Instead using these
    // int A = 0;
    // int B = 1;
    // int C = 2;

    // We use this
    enum Choose { A, B, C };
    // You cannot name the `enum` with same fields (choices)
    enum AnotherChoose {
        A_0 = 0,
        B_1 = 2,
        C_2 = 100,
    };
    LOG(INFO) << "Selection from Enum: " << Choose::A << RESET;
    LOG(INFO) << "Selection from Enum: " << Choose::B << RESET;
    LOG(INFO) << "Selection from Enum: " << Choose::C << RESET;

    // We can create also the `enum` object with a specific choice.
    Choose my_selection = C;
    LOG(INFO) << "My selection from Enum: " << my_selection << RESET;

    // ---------------------------------
    //   Using the Log Class Example
    // ---------------------------------
    Log log_obj = Log();  //<- or simply Log log_obj;
    // <type> name = class_name::type_enum::enum_variate
    Log::Level my_level = Log::Level::LogLevelError;  // Log::LogLevelError this is also working

    log_obj.SetLevel(my_level);  // <- You can pass this directly Log::LogLevelError

    const char* my_message = "This is a testing, maybe an error ..";

    log_obj.Error(my_message);
    log_obj.Warn(my_message);
    log_obj.Info(my_message);
}

// Class Method Definition
void Log::SetLevel(Level level) { m_LogLevel = level; }

void Log::Error(const char* message) {
    if (m_LogLevel >= Level::LogLevelError) {
        std::cout << RED << "[ERROR]: " << BLUE << message << std::endl;
    }
}
void Log::Warn(const char* message) {
    if (m_LogLevel >= Level::LogLevelWarning) {
        std::cout << RED << "[WARN]: " << BLUE << message << std::endl;
    }
}

void Log::Info(const char* message) {
    if (m_LogLevel >= Level::LogLevelInfo) {
        std::cout << RED << "[INFO]: " << BLUE << message << std::endl;
    }
}
