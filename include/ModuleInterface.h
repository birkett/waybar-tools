#ifndef MODULE_INTERFACE_H
#define MODULE_INTERFACE_H

#include <string>

class ModuleInterface
{
public:
    virtual ~ModuleInterface() = default;

    virtual std::string getOutput() = 0;
};

#endif //MODULE_INTERFACE_H
