#include <glog/logging.h>
#include <iostream>
#include <string>
#include <vector>
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

/**
 * Calculates the weighted average of a set of scores.
 *
 * This function computes the weighted average of a series of scores, which can represent
 * grades, ratings, or any other quantifiable metric that benefits from weighted evaluation.
 * Each score is multiplied by its corresponding weight, and the sum of these products is
 * then divided by the sum of the weights. This approach gives different importance to each
 * score based on its weight, allowing for more nuanced calculations than a simple average.
 *
 * @param scores A std::vector<float> containing the scores to be averaged. Each element in
 *               this vector represents a distinct score. Scores must be non-negative.
 * @param weights A std::vector<float> containing the weights corresponding to each score.
 *                Each weight amplifies the importance of its corresponding score in the
 *                calculation of the weighted average. Weights must be non-negative and the
 *                sum of weights must not be zero.
 * @return The weighted average as a float. Returns -1 if the input vectors are of different
 *         sizes, if any score or weight is negative, or if the sum of the weights is zero,
 *         indicating an error in input.
 *
 * Example:
 *   std::vector<float> scores = {90.0, 85.0, 88.0};
 *   std::vector<float> weights = {0.2, 0.5, 0.3};
 *   float weightedAverage = CalculateWeightedAverage(scores, weights);
 *   // weightedAverage would be calculated as follows: (90.0*0.2 + 85.0*0.5 + 88.0*0.3) /
 * (0.2+0.5+0.3)
 */
float CalculateWeightedAverage(const std::vector<float>& scores,
                               const std::vector<float>& weights) {
    // Function implementation goes here.
    if (scores.size() == weights.size()) {
        float output = 0.0f;
        std::vector<float> output_vect;
        for (size_t i = 0; i < scores.size(); i++) {
            output_vect.push_back(scores[i] * weights[i]);
        }
        for (size_t i = 0; i < output_vect.size(); i++) {
            output += output_vect[i];
        }
        return (output / (float)output_vect.size());
    }
    return 0.0;
}

/**
 * Print Nicely the Vector input
 *
 * This function will print the float-type vector nicely in C++
 *
 * @param  v A std::vector<float> containing the scores to be averaged. Each element in
 *               this vector represents a distinct score. Scores must be non-negative.
 * @return Just printing the vector to the standard output in C++ .
 * Example:
 *   std::vector<float> scores = {90.0, 85.0, 88.0};
 *   PrintMyVector(scores);
 *   // will print nicely the: {90.0 , 85.0, 88.0} /
 */
void PrintMyVector(std::vector<float>& v) {
    std::cout << "{ ";
    for (size_t i = 0; i < v.size(); i++) {
        std::cout << YELLOW << v[i] << ", " << RESET;
    }
    std::cout << "} " << std::endl;
}
