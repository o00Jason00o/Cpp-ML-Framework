// Dataset.cpp
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
    return this->headers.size();
}

void Dataset::set_train(double p) {
    if (p < 0 || p > 1)
        throw runtime_error("attempting to set an invalid train_percent");
    else
        this->train_percent = p;
}

double Dataset::get_train_value() {
    return train_percent;
}

pair<vector<vector<string>>, vector<string>> Dataset::get_train() {
    return get_train(this->train_percent);
}

pair<vector<vector<string>>, vector<string>> Dataset::get_train(double percent) {
    size_t split_idx = static_cast<size_t>(percent * this->features.size());
    return {vector<vector<string>>(this->features.begin(), this->features.begin() + split_idx),
            vector<string>(this->labels.begin(), this->labels.begin() + split_idx)};
}

pair<vector<vector<string>>, vector<string>> Dataset::get_test() {
    return get_test(1 - this->train_percent);
}

pair<vector<vector<string>>, vector<string>> Dataset::get_test(double percent) {
    size_t split_idx = this->features.size() - static_cast<size_t>(percent * this->features.size());
    return {vector<vector<string>>(this->features.begin() + split_idx, this->features.end()),
            vector<string>(this->labels.begin() + split_idx, this->labels.end())};
}

// Util functions
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

void Dataset::remove_column(size_t column_index) {
    if (column_index >= features[0].size()) {
        throw std::out_of_range("Invalid column index.");
    }

    for (auto& row : features) {
        row.erase(row.begin() + column_index);
    }

    if (contains_headers && column_index < headers.size()) {
        headers.erase(headers.begin() + column_index);
    }

    if (column_index == static_cast<size_t>(labels_index)) {
        labels.clear();
        labels_index = -1;
    } else if (column_index < static_cast<size_t>(labels_index)) {
        labels_index--;
    }
}

void Dataset::normalize_column(size_t column_index) {

    if(column_index >= size()) {
        throw out_of_range("Column index out of range");
    }

    double mean = 0.0;
    double stdDev = 0.0;
    for(const auto& row : features) {
        mean += stod(row[column_index]); // Assuming the feature is of type double
    }
    mean /= features.size();

    for(const auto& row : features) {
        stdDev += pow(stod(row[column_index]) - mean, 2);
    }
    stdDev = sqrt(stdDev / features.size());

    // Normalizing the column values using z-score normalization
    for(auto& row : features) {
        double value = stod(row[column_index]);
        value = (value - mean) / stdDev;
        row[column_index] = to_string(value);
    }
}

// structure written by ChatGPT
void Dataset::print() const {
    // Width calculations
    int label_max_width = 0;
    if (labels_index != -1) {
        label_max_width = std::max(label_max_width, static_cast<int>(std::string("Labels").size()));
    }

    std::vector<int> feature_max_widths(features[0].size(), 0);
    if (contains_headers) {
        for (size_t i = 0; i < headers.size(); ++i)
            feature_max_widths[i] = headers[i].size();
    }

    for (const auto& feature_row : features) {
        for (size_t i = 0; i < feature_row.size(); ++i) {
            feature_max_widths[i] = std::max(feature_max_widths[i], static_cast<int>(feature_row[i].size()));
        }
    }

    // Printing headers
    if (labels_index != -1) {
        std::cout << std::left << std::setw(label_max_width + 1) << "Labels";
    }

    if (contains_headers) {
        for (size_t i = 0; i < headers.size(); ++i) {
            std::cout << std::left << std::setw(feature_max_widths[i]) << headers[i] << " ";
        }
        std::cout << "\n";
    }

    // Printing data
    for (size_t i = 0; i < features.size(); ++i) {
        if (labels_index != -1) {
            std::cout << std::left << std::setw(label_max_width + 1) << labels[i];
        }
        
        for (size_t j = 0; j < features[i].size(); ++j) {
            std::cout << std::left << std::setw(feature_max_widths[j]) << features[i][j] << " ";
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
