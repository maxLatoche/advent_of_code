#include "file_processor.h"
#include <fstream>
#include <iostream>

int FileProcessor::sumFirstAndLast(const std::string& filePath) {
    std::ifstream file(filePath);

    if (!file.is_open()) {
        std::cerr << "couldn't open file: " << filePath << std::endl;
        return -1;
    }

    int runningTotal = 0;
    std::string line;
    while (std::getline(file, line)) {
        int number = 0;
        int first_number_index = 0;

        for (size_t i = 0; i < line.length(); i++) {
            if (std::isdigit(line[i])) {
                // ascii chars 1 - 9 (ascii 49 to ascii 57) minus '0' (ascii 48) effectively casts to an int
                number = line[i] - '0';

                first_number_index = i;
                break;
            }
        }

        for (size_t i = line.length() - 1; i > first_number_index; i--) {
            if (std::isdigit(line[i])) {
                number = number * 10 + (line[i] - '0');
                break;
            }
        }

        std::cout << "Current number: " << number << ".  Current sum: " << runningTotal << std::endl;
        runningTotal += number;
    }

    file.close();

    return runningTotal;
}
