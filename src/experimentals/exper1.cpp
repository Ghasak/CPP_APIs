#include <iostream>
#include "experimentals/exper1.hpp"
#include "concepts/mylogging.hpp"
#include <vector>
#include <string>
#include <cstdlib>

/**
   ## Two Dimensional Array:
   Function This function for two dimensional array
   @param `None`: for demonstration only, this function accepting no params.

   ## Note:
   The function shows how you allocate on `heap`
   for double pointers (pointer to a pointer) concept
   1. You need to set the size of the data structure
   2. Initialize it
   3. Read it
   4. clean it
 */
void TwoDimensionalArray() {
    size_t ARRAY_SIZE = 0;
    std::cout << "Input the size of the matrix (int) type " << std::endl;
    std::cin >> ARRAY_SIZE;
    /* int* array = new int[ARRAY_SIZE]; */

    int** a2d = new int*[ARRAY_SIZE];

    for (size_t i = 0; i < ARRAY_SIZE; i++) {
        a2d[i] = new int[ARRAY_SIZE];
    }
    // Initialize the array
    for (size_t i = 0; i < ARRAY_SIZE; i++) {
        for (size_t j = 0; j < ARRAY_SIZE; j++) {
            std::cin >> a2d[i][j];
        }
    }

    // print the multi-dimensional array
    for (size_t i = 0; i < ARRAY_SIZE; i++) {
        for (size_t j = 0; j < ARRAY_SIZE; j++) {
            std::cout << ", " << a2d[i][j];
        }
        std::cout << std::endl;
    }

    // Clean up the dynamically allocated memory
    for (size_t i = 0; i < ARRAY_SIZE; i++) {
        delete[] a2d[i];  // Delete each sub-array
    }
    delete[] a2d;
    a2d = nullptr;
}

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
float CalculateWeightedAverage(const std::vector<float>& scores, const std::vector<float>& weights) {
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

void TestingCalcWeigthAeverageFu() {
    std::vector<float> weights = {23.23, 43.23, 44.55};
    std::vector<float> scores = {10.0, 20.0, 5.0};
    PrintMyVector(weights);
    PrintMyVector(scores);
    float result = CalculateWeightedAverage(weights, scores);
    std::cout << BLUE << "Results of calculating average is -> " << MAGENTA << result << RESET << std::endl;
}

/**
 * # Are Equal Function
 * @param T `const&`: first  generic value to be compared with
 * @param T `const&`: second generic value to be compared with
 * This means that you can compare these two values for current objective.
 */
template <typename T>
bool are_equal(T const& a, T const& b) {
    if constexpr (std::is_floating_point_v<T>)
        return std::abs(a - b) < 0.00000001;
    else
        return a == b;
}
/**
 * ## TestingFunction01
 * This function used for testing for the comparing two values
 * What you can make out of this functionality,
 */
void TestingFunction01() {
    std::cout << "Compare01: " << are_equal(1, 1) << std::endl;
    std::cout << "Compare02: " << are_equal(1.999998, 1.999997) << std::endl;
    std::cout << "Compare03: " << are_equal(std::string{"1"}, std::string("1")) << std::endl;
}
