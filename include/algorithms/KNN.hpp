//KNN.hpp
#pragma once
#include <vector>
#include <string>
#include "dataset/Dataset.hpp"

class KNN {

public:
    explicit KNN(int neighbors = 3);


    void setN(int n);
    int getN();

    void set_dataset(const Dataset& data);
    Dataset get_dataset() const;

    //assumes the values in the rows can be converted to double
    double calculate_distance(vector<string> test, vector<string> train);

    string predict_by_majority(const vector<string>& instance);
    string predict_by_average(const vector<string>& instance);

    void fit(const Dataset& data, int n = 3);
    double score(const std::vector<std::string>& true_labels, const std::vector<std::string>& pred_labels);

    vector<string> get_predictions(const vector<vector<string>>& test_features);
    double evaluate();

private:
    size_t neighbors;
    Dataset dataset;
};
