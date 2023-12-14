#include "file_processor.h"
#include <fstream>
#include <iostream>

int FileProcessor::countLines(const std::string& filePath) {
    std::ifstream file(filePath);

    if (!file.is_open()) {
        std::cerr << "couldn't open file: " << filePath << std::endl;
        return -1;
    }

    int lineCount = 0;
    std::string line;
    while (std::getline(file, line)) {
        lineCount++;
    }

    file.close();

    return lineCount;
}
