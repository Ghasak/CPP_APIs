#include <glog/logging.h>
#include <iostream>
#include <string>
#include "concepts/mylogging.hpp"

/**
 * Initializes logging functionality for the application.
 *
 * This function sets up Google's logging library (glog) for the application, configuring
 * the directory where log files will be stored and how logging output is handled. It uses
 * an environment variable 'PROJECT_DIR_2' to dynamically determine the base directory for
 * log files, appending 'src/logs' to this path to specify the log directory. The function
 * also configures glog to determine whether log messages are printed to stderr, the log
 * files, or both, based on the provided flags.
 *
 * @param my_argv The command line arguments passed to the main function of the application,
 *                where my_argv[0] is expected to be the name of the executable. This is used
 *                to initialize Google's logging library with the name of the program.
 *
 * Environment Variables:
 * - PROJECT_DIR_2: Specifies the base directory of the project. This environment variable
 *   must be set prior to calling this function. If not set, the function may not behave as
 *   expected, potentially causing logging to be initialized in an unintended directory.
 *
 * Side Effects:
 * - Sets global flags (FLAGS_logtostderr, FLAGS_alsologtostderr, FLAGS_log_dir) to configure
 *   the behavior of the logging system.
 * - Initializes the Google logging library with the program name and log directory path.
 * - Outputs the final log directory path to standard output for verification.
 *
 * Note: This function does not return a value. Ensure that the 'PROJECT_DIR_2' environment
 * variable is set before calling this function to avoid unexpected behavior. Also, consider
 * the implications of the logging flags for your application's logging strategy.
 */
void init_logging(char** my_argv) {
    // Initialize Google's logging library after setting FLAGS_log_dir
    google::InitGoogleLogging(my_argv[0]);
    const char* projectDir = getenv("PROJECT_DIR_2");
    std::string logDirPath = std::string(projectDir) + "src/logs";
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
