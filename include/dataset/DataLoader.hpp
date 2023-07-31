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


private:
    std::string filePath;
    
};