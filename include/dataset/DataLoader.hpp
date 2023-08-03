//DataLoader.hpp
#pragma once
#include <vector>
#include <string>

class Dataset;

class DataLoader {

public:
    //Constructer for DataLoader, takes in a filepath to compile
    DataLoader(const std::string& filePath);

    Dataset load();

    Dataset load(bool contains_headers, int labels_index);

private:
    std::string filePath;
    
};