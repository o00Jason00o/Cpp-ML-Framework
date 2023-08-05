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
    vector<string> labels;

    void remove_column(size_t columnIndex);

    void set_train(double p);
    double get_train_value();

    // Utility functions
    size_t size() const; // Returns the number of data points

    void shuffle_features();
    
    pair<vector<vector<string>>, vector<string>> get_train();
    pair<vector<vector<string>>, vector<string>> get_train(double percent);
    pair<vector<vector<string>>, vector<string>> get_test();
    pair<vector<vector<string>>, vector<string>> get_test(double percent);

    void print() const;
    void dumb_print() const;

private:
    double train_percent = 0.8;
    
};