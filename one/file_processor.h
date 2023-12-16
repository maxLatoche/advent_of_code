#ifndef FILE_PROCESSOR_H
#define FILE_PROCESSOR_H

#include <string>

class FileProcessor {
public:
    static int sumFirstAndLast(const std::string& filePath);
    static int sumFirstAndLastWithStrings(const std::string& filePath);

private:
    int findNamedNumber(const std::string& str);
};

#endif
