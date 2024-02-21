#include <glog/logging.h>
#include <iostream>
#include <string>

/*
How to use it:
LOG(INFO) << i;
LOG(WARNING) << i;
LOG(ERROR) << i;
*/
void init_logging(char** my_argv) {
    // Initialize Google's logging library after setting FLAGS_log_dir
    google::InitGoogleLogging(my_argv[0]);
    const char* projectDir = getenv("PROJECT_DIR_2");
    std::string logDirPath = std::string(projectDir) + "/src/logs";
    std::cout << logDirPath << std::endl;

    // Set logging flags

    FLAGS_logtostderr = 0;      // 1: don't print error messages to the log files, 0:
                                // print to the log files
    FLAGS_alsologtostderr = 1;  // 1: print error messages to the console, 0: don't print.
    FLAGS_log_dir = logDirPath.c_str();

    // Set log file name extension
    // google::SetLogFilenameExtension(".log");
}

void log_info(const char* message) { LOG(INFO) << message; }
