//DataLoader.cpp
#include "DataLoader.hpp"
#include "Dataset.hpp"
#include <fstream>
#include <sstream>

DataLoader::DataLoader(const std::string& filePath) : filePath(filePath) {
    
}

Dataset DataLoader::load() {
    Dataset dataset;
    std::ifstream file(this->filePath);

    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file.");
    }

    std::string line;

    while(getline(file, line)) {
        std::istringstream ss(line);

        std::vector<std::string> row;
        std::string value;

        while(getline(ss, value, ',')) {
            row.push_back(value);
        }
    }
}