//KNN.hpp
#pragma once
#include <vector>
#include <string>
#include "dataset/Dataset.hpp"

class KNN {

public:
    explicit KNN(int neighbors = 3);
    void train();
    std::vector<double> weights();

    std::vector<int> predict(const Dataset& data);
    void setN(int n);
    int getN();

    void setDataset(const Dataset& data);
    Dataset getDataset() const;

private:
    int neighbors;
    Dataset dataset;
};
