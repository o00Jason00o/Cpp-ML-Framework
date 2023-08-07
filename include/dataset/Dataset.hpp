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

    void set_train(double p);
    double get_train_value();

    // Utility functions
    size_t size() const; // Returns the number of data points

    vector<string> get_column(size_t column_index) const;
    void remove_column(size_t column_index);
    void shuffle_features();
    void normalize_column(size_t column_index);
    
    pair<vector<vector<string>>, vector<string>> get_train() const;
    pair<vector<vector<string>>, vector<string>> get_train(double percent) const;
    pair<vector<vector<string>>, vector<string>> get_test() const;
    pair<vector<vector<string>>, vector<string>> get_test(double percent) const;


    void print() const;
    void dumb_print() const;

private:
    double train_percent = 0.8;
    
};