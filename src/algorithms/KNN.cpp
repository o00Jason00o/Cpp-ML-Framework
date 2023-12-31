//KNN.cpp
#include <vector>
#include <string>
#include <stdexcept>
#include <cmath>
#include <algorithm>
#include <algorithms/KNN.hpp>
#include <dataset/Dataset.hpp>
#include <map>

using namespace std;

KNN::KNN(int neighbors) : neighbors(neighbors) {}; 

void KNN::set_dataset(const Dataset& data) {
    this->dataset = data;
}

Dataset KNN::get_dataset() const {
    return this->dataset;
}

void KNN::setN(int n) {
    this->neighbors = n;
}

int KNN::getN() {
    return this->neighbors;
}

double KNN::calculate_distance(vector<string> row1, vector<string> row2) {

    if(row1.size() != row2.size())
        throw runtime_error("Inconsistent row size");
    double error = 0;

    for (size_t i = 0; i < row1.size() && i < row2.size(); ++i) {
        double value1, value2;

        try {
            value1 = stod(row1[i]);
            value2 = stod(row2[i]);
        } catch (const invalid_argument&) {
            throw runtime_error("Failed to convert string to double due to invalid argument.");
        } catch (const out_of_range&) {
            throw runtime_error("Failed to convert string to double due to out of range.");
        }
        error += (value1 - value2) * (value1 - value2);
    }

    return sqrt(error);
}

void KNN::fit(const Dataset& data, int n) {
    this->setN(n);
    set_dataset(data);
}

string KNN::predict_by_majority(const vector<string>& instance) {
    // Store all distances and their associated labels
    vector<pair<double, string>> distances_with_labels;

    for (size_t i = 0; i < dataset.features.size(); ++i) {
        const auto& row = dataset.features[i];
        double dist = calculate_distance(row, instance);
        string label = dataset.labels[i];
        distances_with_labels.push_back({dist, label});
    }

    // Sort the distances
    sort(distances_with_labels.begin(), distances_with_labels.end());

    // Logic to count the occurrences of the labels among the top k neighbors
    map<string, int> label_count;
    for (size_t i = 0; i < neighbors && i < distances_with_labels.size(); ++i) {
        label_count[distances_with_labels[i].second]++;
    }

    int max_count = -1;
    string most_common_label;
    for (auto& pair : label_count) {
        if (pair.second > max_count) {
            max_count = pair.second;
            most_common_label = pair.first;
        }
    }

    return most_common_label;
}

//isn't implemented yet in evaluate and score
string KNN::predict_by_average(const vector<string>& instance) {
    // Store all distances and their associated labels
    vector<pair<double, string>> distances_with_labels;

    for (size_t i = 0; i < dataset.features.size(); ++i) {
        const auto& row = dataset.features[i];
        double dist = calculate_distance(row, instance);
        string label = dataset.labels[i];
        distances_with_labels.push_back({dist, label});
    }

    // Sort the distances
    sort(distances_with_labels.begin(), distances_with_labels.end());

    double sum = 0;
    for (size_t i = 0; i < neighbors && i < distances_with_labels.size(); ++i) {
        sum += stod(distances_with_labels[i].second);
    }

    return to_string(sum / neighbors);
}

double KNN::score(const vector<string>& true_labels, const vector<string>& pred_labels) {
    if(true_labels.size() != pred_labels.size())
        throw runtime_error("Inconsistent label size");

    int correct_count = 0;
    for (size_t i = 0; i < true_labels.size(); ++i) {
        if(true_labels[i] == pred_labels[i])
            correct_count++;
    }

    return static_cast<double>(correct_count) / true_labels.size();
}

vector<string> KNN::get_predictions(const vector<vector<string>>& test_features) {
    vector<string> predictions;

    for(vector<string> row : test_features) {
        predictions.push_back(predict_by_majority(row));
    }

    return predictions;
}

double KNN::evaluate() {

    pair<vector<vector<string>>, vector<string>> test_data = dataset.get_test();
    vector<string> predictions;

    for(vector<string> row : test_data.first) {
        predictions.push_back(predict_by_majority(row));
    }

    double test_score = score(test_data.second, predictions);

    return test_score;
}