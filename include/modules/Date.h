#ifndef DATE_H
#define DATE_H

#include <chrono>
#include <string>

#include "ModuleInterface.h"

class Date : public ModuleInterface
{
public:
    Date() { this->tt = 0; };
    ~Date() = default;

    std::string getOutput() final;

private:
    time_t tt;
};

#endif //DATE_H
