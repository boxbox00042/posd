#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

class FileReader
{
private:
    std::string _filePath;

public:
    FileReader(std::string filePath) : _filePath(filePath) {}

    std::string read()
    {
        std::ifstream ifs(_filePath, std::ios::in);
        if (!ifs.is_open())
            throw "Failed to open file.";
        std::stringstream ss;
        ss << ifs.rdbuf();
        std::string result(ss.str());
        ifs.close();
        return result;
    }
};