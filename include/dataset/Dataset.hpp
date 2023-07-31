//Dataset.hpp
#pragma once

#include <vector>
#include <string>

class Dataset {

public:
    Dataset();

    std::vector<std::string> headers;
    std::vector<std::vector<std::string>> features;
    std::vector<int> labels; 

    // Utility functions
    size_t size() const; // Returns the number of data points
    

private:
    
};