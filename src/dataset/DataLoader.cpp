//DataLoader.cpp
#include "dataset/DataLoader.hpp"
#include "dataset/Dataset.hpp"
#include <fstream>
#include <sstream>

DataLoader::DataLoader(const std::string& filePath) : filePath(filePath) {
    
}

Dataset DataLoader::load() {
    return this->load(true, -1);
}

Dataset DataLoader::load(bool contains_headers, int labels_index) {
    Dataset dataset;
    dataset.contains_headers = contains_headers;
    dataset.labels_index = labels_index;
    std::ifstream file(this->filePath);

    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + this->filePath);
    }

    std::string line;

    // Compile the headers
    if (contains_headers && getline(file, line)) {
        std::istringstream ss(line);
        std::string value;

        int col_index = 0;
        while (getline(ss, value, ',')) {
            if (col_index == labels_index) {
                col_index++;
                continue;
            }
            dataset.headers.push_back(value);
            col_index++;
        }
    }

    // Compile the features & labels
    while (getline(file, line)) {
        std::istringstream ss(line);

        std::vector<std::string> row;
        std::string value;

        int col_index = 0;
        while (getline(ss, value, ',')) {
            if (col_index == labels_index) {
                dataset.labels.push_back(value);
            } else {
                row.push_back(value);
            }
            col_index++;
        }

        dataset.features.push_back(row);
    }

    return dataset;
}
