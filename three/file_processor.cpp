#include "file_processor.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <numeric>
#include <tuple>

int FileProcessor::numberFinder(const std::string &filePath)
{
    std::ifstream file(filePath);

    if (!file.is_open())
    {
        std::cerr << "couldn't open file: " << filePath << std::endl;
        return -1;
    }

    int runningTotal = 0;
    std::vector<std::vector<char>> linesArr;
    std::string line;
    while (std::getline(file, line))
    {
        std::vector<char> charRow;
        for (char c : line) {
            charRow.push_back(c);
        }

        linesArr.push_back(charRow);
    }



    file.close();

    return runningTotal;
}
