//DataLoader.hpp
#pragma once

#include <string>
#include <vector>

class Dataset;

class DataLoader {

public:

    //Constructer for DataLoader, takes in a filepath to compile
    DataLoader(const std::string& filePath);

    Dataset load();


private:
    std::string filePath;
    //Include any other private helper methods or attributes here

};