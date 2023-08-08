// LinearRegression.cpp
#include "algorithms/LinearRegression.hpp"
#include <iostream>
#include <cmath>
#include <algorithm>

LinearRegression::LinearRegression()
    : alpha(0.01), iterations(1000), bias(0.0) {}

vector<double> strings_to_doubles(const vector<string>& string_vec) {
    vector<double> double_vec;
    std::transform(string_vec.begin(), string_vec.end(), std::back_inserter(double_vec), [](const string& s) {
        return std::stod(s);
    });
    return double_vec;
}

vector<vector<double>> strings_to_doubles_2d(const vector<vector<string>>& string_vec_2d) {
    vector<vector<double>> double_vec_2d;
    for (const auto& vec : string_vec_2d) {
        double_vec_2d.push_back(strings_to_doubles(vec));
    }
    return double_vec_2d;
}

void LinearRegression::fit(const Dataset& dataset, double alpha, int iterations) {
    this->alpha = alpha;
    this->iterations = iterations;

    // Convert string values to double
    vector<vector<double>> X = strings_to_doubles_2d(dataset.get_train().first);
    vector<double> Y = strings_to_doubles(dataset.get_train().second);

    size_t n = X.size();
    size_t m = X[0].size(); // number of features

    weights.assign(m, 0.0); // Initialize weights to zeros

    for (int iter = 0; iter < this->iterations; ++iter) {
        vector<double> Y_predicted(n, 0.0);

        // Calculate predicted values
        for (size_t i = 0; i < n; ++i) {
            for (size_t j = 0; j < m; ++j) {
                Y_predicted[i] += X[i][j] * weights[j];
            }
            Y_predicted[i] += bias;
        }

        // Calculate gradients
        vector<double> dW(m, 0.0);
        double dB = 0.0;

        for (size_t i = 0; i < n; ++i) {
            double error = Y_predicted[i] - Y[i];
            for (size_t j = 0; j < m; ++j) {
                dW[j] += X[i][j] * error;
            }
            dB += error;
        }

        // Update weights and bias using gradient
        for (size_t j = 0; j < m; ++j) {
            weights[j] -= (this->alpha / n) * dW[j];
        }
        bias -= (this->alpha / n) * dB;
    }
}

double LinearRegression::compute_mse(const Dataset& dataset) {
    vector<vector<double>> X = strings_to_doubles_2d(dataset.get_test().first);
    vector<double> Y = strings_to_doubles(dataset.get_test().second);
    size_t n = X.size();

    double mse = 0.0;

    for (size_t i = 0; i < n; ++i) {
        double prediction = bias;
        for (size_t j = 0; j < X[i].size(); ++j) {
            prediction += X[i][j] * weights[j];
        }
        mse += std::pow(Y[i] - prediction, 2);
    }

    cout << weights[0] << endl;
    return mse / n;
}
