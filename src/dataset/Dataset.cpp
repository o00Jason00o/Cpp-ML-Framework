//Dataset.cpp
#include "dataset/Dataset.hpp"
#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <random>
using namespace std;

Dataset::Dataset() {}

size_t Dataset::size() const {
    return this->features.size();
}

void Dataset::set_train(double p) {
    if (p < 0 || p > 1)
        throw runtime_error("attemping to set an invalid train_percent");
    else
        this->train_percent = p;
}

double Dataset::get_train_value() {
    return train_percent;
}


//Utility functions

vector<vector<string>> Dataset::get_train() {
    return get_train(this->train_percent);
}

vector<vector<string>> Dataset::get_train(double percent) {
    size_t splitIdx = static_cast<size_t>(percent * this->features.size());
    return vector<vector<string>>(this->features.begin(), this->features.begin() + splitIdx);
}

vector<vector<string>> Dataset::get_test() {
    return get_test(1 - this->train_percent);
}

vector<vector<string>> Dataset::get_test(double percent) {
    size_t splitIdx = this->features.size() - static_cast<size_t>(percent * this->features.size());
    return vector<vector<string>>(this->features.begin() + splitIdx, this->features.end());
}

void Dataset::shuffle_features() {
    // Use a random device to seed the random number generator
    std::random_device rd;
    std::mt19937 g(rd());

    // Create a vector of pairs from features and labels
    std::vector<std::pair<vector<string>, string>> combined;
    for (size_t i = 0; i < features.size(); ++i) {
        combined.push_back({features[i], labels[i]});
    }
    
    // Shuffle the combined vector
    std::shuffle(combined.begin(), combined.end(), g);

    // Split the shuffled combined vector back into features and labels
    for (size_t i = 0; i < combined.size(); ++i) {
        features[i] = combined[i].first;
        labels[i] = combined[i].second;
    }
}



//structure written by ChatGPT
void Dataset::print() const {
    // Width calculations
    int labelMaxWidth = 0;
    if (labels_index != -1) {
    labelMaxWidth = std::max_element(labels.begin(), labels.end(), 
                                     [](const string& a, const string& b) { return a.size() < b.size(); })->size();
    }

    std::vector<int> featureMaxWidths(features[0].size(), 0);
    if (contains_headers) {
        for (size_t i = 0; i < headers.size(); ++i)
            featureMaxWidths[i] = headers[i].size();
    }

    for (const auto& featureRow : features) {
        for (size_t i = 0; i < featureRow.size(); ++i) {
            featureMaxWidths[i] = std::max(featureMaxWidths[i], static_cast<int>(featureRow[i].size()));
        }
    }

    // Printing headers
    if (labels_index != -1) {
        std::cout << std::left << std::setw(labelMaxWidth) << "Labels" << " ";
    }

    if (contains_headers) {
        for (size_t i = 0; i < headers.size(); ++i) {
            std::cout << std::left << std::setw(featureMaxWidths[i]) << headers[i] << " ";
        }
        std::cout << "\n";
    }

    // Printing data
    for (size_t i = 0; i < features.size(); ++i) {
        if (labels_index != -1) {
            std::cout << std::left << std::setw(labelMaxWidth) << labels[i] << " ";
        }
        
        for (size_t j = 0; j < features[i].size(); ++j) {
            std::cout << std::left << std::setw(featureMaxWidths[j]) << features[i][j] << " ";
        }
        std::cout << "\n";
    }
}


void Dataset::dumb_print() const {
    cout << "headers: " << endl; 
    for (string box : this->headers) {
        cout << box << " ";
    }
    cout << endl;

    cout << "labels: " << endl; 
    for (string box : this->labels) {
        cout << box << " ";
    }
    cout << endl;

    cout << "features: " << endl; 
    for (vector<string> row : features) {
        for (string box : row) {
            cout << box << " ";
        }
        cout << endl;
    }
}