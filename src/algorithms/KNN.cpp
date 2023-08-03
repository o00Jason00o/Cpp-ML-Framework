//KNN.cpp
#include <vector>
#include <string>
#include <algorithms/KNN.hpp>
#include <dataset/Dataset.hpp>


KNN::KNN(int neighbors) : neighbors(neighbors) {}; 

void KNN::setDataset(const Dataset& data) {
    this->dataset = data;
}

Dataset KNN::getDataset() const {
    return this->dataset;
}

void KNN::setN(int n) {
    this->neighbors = n;
}

int KNN::getN() {
    return this->neighbors;
}

void train(const Dataset& data) {
    
}