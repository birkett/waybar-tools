#include "modules/Battery.h"
#include "SysFs.h"

std::string Battery::batteryStatus()
{
    return loadStringFromSysFs("/sys/class/power_supply/BAT0/status");
}

int Battery::batteryCharge()
{
    return loadIntFromSysFs("/sys/class/power_supply/BAT0/charge_now");
}

std::string Battery::batteryIcon(int charge)
{
    if (charge < 10) {
        return "\uF244"; // Battery empty icon.
    }

    if (charge < 33) {
        return "\uF243"; // Battery quarter icon.
    }

    if (charge < 66) {
        return "\uF242"; // Battery half icon.
    }

    if (charge < 90) {
        return "\uF241"; // Battery three quarters icon.
    }

    return "\uF240"; // Battery full icon.
}

unsigned short Battery::getRefreshTimeMs()
{
    return 1000;
}

std::string Battery::getOutput()
{
    int charge = batteryCharge();
    std::string outputString;

    outputString.append(batteryStatus());
    outputString.append(" - ");
    outputString.append(std::to_string(charge));
    outputString.append("% ");
    outputString.append(batteryIcon(charge));

    return outputString;
}
