#include "modules/Date.h"

unsigned short Date::getRefreshTimeMs()
{
    return 1000;
}

std::string Date::getOutput()
{
    this->tt = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

    char buffer[32];

    std::strftime(buffer, sizeof(buffer), "%a %d %b %T %Z %Y", std::localtime(&this->tt));

    return { buffer };
}
