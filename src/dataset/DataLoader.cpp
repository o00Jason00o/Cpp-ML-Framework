//DataLoader.cpp
#include "dataset/DataLoader.hpp"
#include "dataset/Dataset.hpp"
#include <fstream>
#include <sstream>

DataLoader::DataLoader(const std::string& filePath) : filePath(filePath) {
    
}

Dataset DataLoader::load() {
    Dataset dataset;
    std::ifstream file(this->filePath);

    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file." + this->filePath);
    }

    std::string line;

    //compile the headers
    if(getline(file, line)) {
        std::istringstream ss(line);
        std::string value;

        getline(ss, value, ','); //hard coded to remove the header that says "Label"
                                 //because we are assuming that labels are in the first column

        //store the headers
        while(getline(ss, value, ',')) {
            dataset.headers.push_back(value);
        }

    } else {
        throw std::runtime_error("File is empty");
    }

    //compile the features & labels
    while(getline(file, line)) {
        std::istringstream ss(line);

        std::vector<std::string> row;
        std::string value;

        //store the label (first value in each line) in the labels vector
        if(!getline(ss, value, ',')) {
            throw std::runtime_error("Failed to get line");
        } else {
            dataset.labels.push_back(std::stoi(value));
        }

        //process the features and store them in the features vector
        while(getline(ss, value, ',')) {
            row.push_back(value);
        }

        dataset.features.push_back(row);
    }

    return dataset;
}