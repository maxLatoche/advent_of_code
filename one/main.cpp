#include "file_processor.h"
#include <iostream>

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << "<file_path>" << std::endl;

        return 1;
    }

    std::string filePath = argv[1];

    int lineCount = FileProcessor::countLines(filePath);

    if (lineCount > 0) {
        std::cout << "output: " << lineCount << std::endl;
    }

    return 0;
}