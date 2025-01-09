#include <glog/logging.h>
#include <filesystem>
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
    // Initialize Google's logging library
    google::InitGoogleLogging(my_argv[0]);

    // Retrieve PROJECT_DIR_2 environment variable
    const char* projectDir = getenv("PROJECT_DIR_2");
    if (!projectDir) {
        std::cerr << "Error: PROJECT_DIR_2 environment variable is not set.\n";
        exit(EXIT_FAILURE);
    }

    // Normalize project directory path by removing quotes and trailing slashes
    std::string projectDirStr = std::string(projectDir);

    // Remove surrounding quotes if they exist
    if (!projectDirStr.empty() && projectDirStr.front() == '"' && projectDirStr.back() == '"') {
        projectDirStr = projectDirStr.substr(1, projectDirStr.size() - 2);
    }

    // Remove trailing slash if present
    if (!projectDirStr.empty() && projectDirStr.back() == '/') {
        projectDirStr.pop_back();
    }

    // Set the log directory path
    std::string logDirPath = projectDirStr + "/src/logs";

    // Ensure the log directory exists
    if (!std::filesystem::exists(logDirPath)) {
        std::filesystem::create_directories(logDirPath);
    }

    // Debugging output for log directory creation
    if (std::filesystem::exists(logDirPath)) {
        std::cout << "Log directory created successfully: " << logDirPath << std::endl;
    } else {
        std::cerr << "Failed to create log directory: " << logDirPath << std::endl;
        exit(EXIT_FAILURE);
    }

    // Set logging flags
    FLAGS_logtostderr = 0;  // Logs to files instead of stderr
    FLAGS_alsologtostderr = 1;  // Also log to stderr
    FLAGS_log_dir = logDirPath;

    // Debugging: print FLAGS_log_dir
    std::cout << "FLAGS_log_dir is set to: " << FLAGS_log_dir << std::endl;

    // Log initialization message
    LOG(INFO) << "Logging initialized. Logs will be written to " << logDirPath;
}

void log_info(const char* message) { LOG(INFO) << message; }
