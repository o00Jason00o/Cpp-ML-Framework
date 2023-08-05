//Dataset.cpp
#include "dataset/Dataset.hpp"
#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <random>
#include <numeric>
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

void Dataset::remove_column(size_t columnIndex) {
    if (columnIndex >= features[0].size()) {
        throw std::out_of_range("Invalid column index.");
    }

    for (auto& row : features) {
        row.erase(row.begin() + columnIndex);
    }

    if (contains_headers && columnIndex < headers.size()) {
        headers.erase(headers.begin() + columnIndex);
    }

    if (columnIndex == static_cast<size_t>(labels_index)) {
        labels.clear();
        labels_index = -1;
    } else if (columnIndex < static_cast<size_t>(labels_index)) {
        labels_index--;
    }
}

pair<vector<vector<string>>, vector<string>> Dataset::get_train() {
    return get_train(this->train_percent);
}

pair<vector<vector<string>>, vector<string>> Dataset::get_train(double percent) {
    size_t splitIdx = static_cast<size_t>(percent * this->features.size());
    return {vector<vector<string>>(this->features.begin(), this->features.begin() + splitIdx),
            vector<string>(this->labels.begin(), this->labels.begin() + splitIdx)};
}

pair<vector<vector<string>>, vector<string>> Dataset::get_test() {
    return get_test(1 - this->train_percent);
}

pair<vector<vector<string>>, vector<string>> Dataset::get_test(double percent) {
    size_t splitIdx = this->features.size() - static_cast<size_t>(percent * this->features.size());
    return {vector<vector<string>>(this->features.begin() + splitIdx, this->features.end()),
            vector<string>(this->labels.begin() + splitIdx, this->labels.end())};
}

void Dataset::shuffle_features() {
    std::random_device rd;
    std::mt19937 g(rd());

    // Create a vector of indices
    std::vector<size_t> indices(features.size());
    std::iota(indices.begin(), indices.end(), 0);  // fill with 0, 1, ..., n-1

    // Shuffle the indices
    std::shuffle(indices.begin(), indices.end(), g);

    // Rearrange the features and labels based on shuffled indices
    vector<vector<string>> shuffled_features(features.size());
    vector<string> shuffled_labels(labels.size());
    
    for (size_t i = 0; i < indices.size(); i++) {
        shuffled_features[i] = features[indices[i]];
        shuffled_labels[i] = labels[indices[i]];
    }

    features = std::move(shuffled_features);
    labels = std::move(shuffled_labels);
}

//structure written by ChatGPT
void Dataset::print() const {
    // Width calculations
    int labelMaxWidth = 0;
    if (labels_index != -1) {
        labelMaxWidth = std::max(labelMaxWidth, static_cast<int>(std::string("Labels").size()));
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
        std::cout << std::left << std::setw(labelMaxWidth + 1) << "Labels";
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
            std::cout << std::left << std::setw(labelMaxWidth + 1) << labels[i];
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