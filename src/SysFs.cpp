#include <fstream>

#include "SysFs.h"

std::string loadStringFromSysFs(const char* fileName)
{
    std::string value;
    std::ifstream file(fileName);
    file >> value;
    file.close();

    return value;
}

int loadIntFromSysFs(const char* fileName)
{
    return std::stoi(loadStringFromSysFs(fileName));
}
