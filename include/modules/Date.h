#ifndef DATE_H
#define DATE_H

#include <chrono>
#include <string>

#include "ModuleInterface.h"

class Date : public ModuleInterface
{
public:
    Date() : tt(0) {};

    std::string getOutput() final;

private:
    time_t tt;
};

#endif //DATE_H
