#include "dataset/DataLoader.hpp"
#include "dataset/Dataset.hpp"
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: ./ml_app <path_to_csv_file>" << std::endl;
        return 1;
    }

    const std::string filePath = argv[1];
    DataLoader loader(filePath);
    Dataset dataset = loader.load();

    std::cout << "running main" << std::endl;
    dataset.print();


    return 0;


}