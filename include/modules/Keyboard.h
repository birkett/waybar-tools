#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <string>

#include "ModuleInterface.h"

class Keyboard : public ModuleInterface
{
public:
    std::string getOutput() final;

private:
    static int capsLockState();
    static int numLockState();
    static int scrollLockState();
};

#endif //KEYBOARD_H
