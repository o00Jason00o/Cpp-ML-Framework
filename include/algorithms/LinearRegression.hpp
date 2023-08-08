//LinearRegression.hpp
#pragma once
#include <vector>
#include <string>
#include "dataset/Dataset.hpp"

class LinearRegression {

public:
    LinearRegression();

    void fit(const Dataset& data, double alpha = 0.01, int iterations = 1000);

    double compute_mse(const Dataset& dataset);


private:
    double alpha;
    int iterations;
    vector<double> weights;
    double bias;
};