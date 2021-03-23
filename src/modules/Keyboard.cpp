#include "modules/Keyboard.h"
#include "SysFs.h"

int Keyboard::capsLockState()
{
    return loadIntFromSysFs("/sys/class/leds/input0::capslock/brightness");
}

int Keyboard::numLockState()
{
    return loadIntFromSysFs("/sys/class/leds/input0::numlock/brightness");
}

int Keyboard::scrollLockState()
{
    return loadIntFromSysFs("/sys/class/leds/input0::scrolllock/brightness");
}

std::string Keyboard::getOutput()
{
    std::string outputString;

    if (capsLockState() > 0) {
        outputString.append("CAPS ");
    }

    if (numLockState() > 0) {
        outputString.append("NUM ");
    }

    if (scrollLockState() > 0) {
        outputString.append("SCROLL ");
    }

    if (outputString.length() > 0) {
        outputString.append("\uF11C\""); // Keyboard icon.
    }

    return outputString;
}
