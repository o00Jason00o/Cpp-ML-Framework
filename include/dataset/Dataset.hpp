//Dataset.hpp
#pragma once

#include <vector>
#include <string>
using namespace std;

class Dataset {

public:
    Dataset();
    bool contains_headers = true;
    int labels_index = -1;

    vector<string> headers;
    vector<vector<string>> features;
    vector<int> labels;

    void set_train(double p);
    double get_train_value();

    // Utility functions
    size_t size() const; // Returns the number of data points

    void shuffle_features();
    
    vector<vector<string>> get_train(); // Use the train_percent of this object
    vector<vector<string>> get_train(double percent); // Use the given percent, get the x 
                                                      //percent of data counting from the top

    vector<vector<string>> get_test();
    vector<vector<string>> get_test(double percent); //get the x percent of data counting from the bottom

    void print() const;
    void dumb_print() const;

private:
    double train_percent = 0.8;
    
};