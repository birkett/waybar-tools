#include "modules/Date.h"

std::string Date::getOutput()
{
    this->tt = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

    char mbstr[32];

    std::strftime(mbstr, sizeof(mbstr), "%a %d %b %T %Z %Y", std::localtime(&this->tt));

    return std::string(mbstr);
}
