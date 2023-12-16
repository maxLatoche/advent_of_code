#include "file_processor.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <set>
#include <tuple>

std::unordered_map<std::string, int> colorLimits = {
    {"red", 13},
    {"green", 14},
    {"blue", 15},
};


std::string trim(const std::string& str) {
    const auto strBegin = str.find_first_not_of(" \t");
    if (strBegin == std::string::npos)
        return ""; // no content

    const auto strEnd = str.find_last_not_of(" \t");
    const auto strRange = strEnd - strBegin + 1;

    return str.substr(strBegin, strRange);
}


bool isRoundValid(const std::string &round)
{
    const char delim = ',';
    const char spaceDelim = ' ';

    std::vector<std::string> parts;
    std::string tempPart;

    std::stringstream ss(round);

    while (std::getline(ss, tempPart, delim))
    {
        parts.push_back(tempPart);
    }

    for (const auto &part : parts)
    {
        std::string color, count;
        std::stringstream ssTwo(trim(part));
        if (std::getline(ssTwo, count, spaceDelim))
        {
            std::getline(ssTwo, color);
        }

        if (std::stoi(count) >= colorLimits[color])
        {
            return false;
        }
    }

    return true;
}

int FileProcessor::countValidGames(const std::string &filePath)
{
    std::ifstream file(filePath);

    if (!file.is_open())
    {
        std::cerr << "couldn't open file: " << filePath << std::endl;
        return -1;
    }

    int runningTotal = 0;
    std::string line;
    while (std::getline(file, line))
    {
        std::string game, rounds, round;
        std::stringstream ssGame(line);
        const char colonDelim = ':';
        const char semicolonDelim = ';';

        if (std::getline(ssGame, game, colonDelim))
        {
            std::getline(ssGame, rounds);
        }

        std::stringstream ssRounds(rounds);
        bool isGameValid = true;
        while (std::getline(ssRounds, round, semicolonDelim))
        {
            if (!isRoundValid(round))
            {
                isGameValid = false;
                break;
            }
        }

        if (isGameValid)
        {
            std::string part1, part2;
            std::stringstream ss(line);
            const char spaceDelim = ' ';

            if (std::getline(ss, part1, spaceDelim))
            {
                std::getline(ss, part2);
            }
            runningTotal += std::stoi(part2);
        }
    }

    return runningTotal;
}
