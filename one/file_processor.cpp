#include "file_processor.h"
#include <fstream>
#include <iostream>
#include <set>
#include <tuple>

int FileProcessor::sumFirstAndLast(const std::string &filePath)
{
    std::ifstream file(filePath);

    if (!file.is_open())
    {
        std::cerr << "couldn't open file: " << filePath << std::endl;
        return -1;
    }

    int runningTotal = 0;
    int lineNum = 0;
    std::string line;
    while (std::getline(file, line))
    {
        lineNum++;
        int number = 0;
        int first_number_index = 0;

        for (size_t i = 0; i < line.length(); i++)
        {
            if (std::isdigit(line[i]))
            {
                // ascii chars 1 - 9 (ascii 49 to ascii 57) minus '0' (ascii 48) effectively casts to an int
                number = line[i] - '0';

                first_number_index = i;
                break;
            }
        }

        for (size_t i = line.length() - 1; i >= first_number_index; i--)
        {
            if (std::isdigit(line[i]))
            {
                number = number * 10 + (line[i] - '0');
                break;
            }
        }

        std::cout << "Line no. " << lineNum << " number: " << number << ".  Current sum: " << runningTotal << std::endl;
        runningTotal += number;
    }

    file.close();

    return runningTotal;
}

static std::unordered_map<std::string, int> numberDictionary = {
    {"zero", 0},
    {"one", 1},
    {"two", 2},
    {"three", 3},
    {"four", 4},
    {"five", 5},
    {"six", 6},
    {"seven", 7},
    {"eight", 8},
    {"nine", 9},
};

// TODO: could dynamically generate this from numberDictionary, also, possibly both in file_processor.h?
static std::set<std::string> mySet = {
    "zero",
    "one",
    "two",
    "three",
    "four",
    "five",
    "six",
    "seven",
    "eight",
    "nine",
};

bool startsWith(const std::string &fullString, const std::string &starting)
{
    if (fullString.length() >= starting.length())
    {
        return fullString.substr(0, starting.length()) == starting;
    }
    return false;
}

int FileProcessor::sumFirstAndLastWithStrings(const std::string &filePath)
{
    std::ifstream file(filePath);

    if (!file.is_open())
    {
        std::cerr << "couldn't open file: " << filePath << std::endl;
        return -1;
    }

    int runningTotal = 0;
    int lineNum = 0;
    std::string line;
    while (std::getline(file, line))
    {
        lineNum++;
        int firstNumber = '\0';
        char maybeLastNumber = '\0';

        for (size_t i = 0; i < line.length(); i++)
        {
            if (std::isdigit(line[i]))
            {
                int thisNumber = line[i];

                if (firstNumber == '\0')
                {
                    firstNumber = thisNumber - '0';
                }
                else
                {
                    maybeLastNumber = thisNumber - '0';
                }
            }
            else
            {
                for (const std::string &element : mySet)
                {
                    if (startsWith(line.substr(i), element))
                    {
                        int thisNumber = numberDictionary[element];

                        if (firstNumber == '\0')
                        {
                            firstNumber = thisNumber;
                        }
                        else
                        {
                            maybeLastNumber = thisNumber;
                        }
                    }
                }
            }
        }

        int secondNumber = - 1;
        if (maybeLastNumber == '\0') {
            // duplicate first number if there is no second number
            secondNumber = firstNumber;
        } else {
            secondNumber = maybeLastNumber;
        }

        std::cout << "firs no. " << firstNumber << std::endl;
        std::cout << "second no. " << secondNumber << std::endl;
        int number = firstNumber * 10 + secondNumber;

        std::cout << "Line no. " << lineNum << " number: " << number << ".  Current sum: " << runningTotal << std::endl;
        runningTotal += number;
    }

    file.close();

    return runningTotal;
}
