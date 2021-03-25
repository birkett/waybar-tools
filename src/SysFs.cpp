#include <fstream>

#include "SysFs.h"

std::string loadStringFromSysFs(const std::string &fileName)
{
    std::string value;
    std::ifstream file(fileName);
    file >> value;
    file.close();

    return value;
}

int loadIntFromSysFs(const std::string &fileName)
{
    return std::stoi(loadStringFromSysFs(fileName));
}
