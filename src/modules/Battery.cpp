#include "modules/Battery.h"
#include "SysFs.h"

std::string Battery::batteryStatus()
{
    return loadStringFromSysFs("/sys/class/power_supply/BAT0/status");
}

std::string Battery::batteryCharge()
{
    return loadStringFromSysFs("/sys/class/power_supply/BAT0/charge_now");
}

std::string Battery::getOutput()
{
    std::string outputString;

    outputString.append(batteryStatus());
    outputString.append(" - ");
    outputString.append(batteryCharge());
    outputString.append("% ");
    outputString.append(""); // Battery icon.

    return outputString;
}
