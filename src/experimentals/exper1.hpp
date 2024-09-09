#include <vector>
#include "concepts/mylogging.hpp"

#pragma once
void TwoDimensionalArray();
// testing function purposes only
float CalculateWeightedAverage(const std::vector<float>&, const std::vector<float>&);
void PrintMyVector(std::vector<float>&);
// testing function in action for showing the power of using std::vector
void TestingCalcWeigthAeverageFu();

// About comapre two values
template <typename T>
bool are_equal(T const&, T const&);
void TestingFunction01();
