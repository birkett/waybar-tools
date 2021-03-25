#ifndef BATTERY_H
#define BATTERY_H

#include <string>

#include "ModuleInterface.h"

class Battery : public ModuleInterface
{
public:
    Battery() = default;
    ~Battery() = default;

    std::string getOutput() final;

private:
    static std::string batteryStatus();
    static int batteryCharge();
    static std::string batteryIcon(int charge);
};

#endif //BATTERY_H
