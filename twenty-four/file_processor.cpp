#include "file_processor.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <tuple>

struct VectorInfo
{
    double m;
    double b;
    double px;
    double py;
    double pz;
    double vx;
    double vy;
    double vz;
};

std::tuple<double, double, double, double, double, double, double, double>
calculateSlopeAndIntercept(const std::string &input)
{
    std::istringstream ss(input);
    double px, py, pz, vx, vy, vz;

    ss >> px >> py >> pz >> vx >> vy >> vz;

    // for y = mx + b
    double m = vy / vx;
    double b = py - m * px;

    return std::make_tuple(m, b, px, py, pz, vx, vy, vz);
}

int FileProcessor::twoDSolution(const std::string &filePath)
{
    std::ifstream file(filePath);

    if (!file.is_open())
    {
        std::cerr << "couldn't open file: " << filePath << std::endl;
        return -1;
    }

    int validIntersections = 0;
    int missed = 0;
    std::unordered_map<std::string, VectorInfo> coords_dictionary;
    std::string line;
    std::vector<std::string> lines;
    while (std::getline(file, line))
    {
        lines.push_back(line);
        auto [m, b, px, py, pz, vx, vy, vz] = calculateSlopeAndIntercept(line);

        coords_dictionary[line] = {
            m,
            b,
            px,
            py,
            pz,
            vx,
            vy,
            vz};
    }

    for (int i = 0; i < lines.size(); i++)
    {
        for (int j = i + 1; j < lines.size(); j++)
        {
            if (!lines[j].empty())
            {
                VectorInfo line1 = coords_dictionary[lines[i]];
                VectorInfo line2 = coords_dictionary[lines[j]];
                // could add parallel and same line checks if we wanted
                // make the equations equal to each other to find the intersection
                // m1x + b1 = m2x + b2
                // x = (b2 - b1) / (m1 - m2)
                double x = (line2.b - line1.b) / (line1.m - line2.m);
                double y = line1.m * x + line1.b;

                if (x >= 200000000000000 && x <= 400000000000000 && y >= 200000000000000 && y <= 400000000000000)
                {
                    validIntersections++;
                }
                else
                {
                    missed++;
                }
            }
        }
    }

    return validIntersections;
}
