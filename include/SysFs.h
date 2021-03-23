#ifndef SYSFS_H
#define SYSFS_H

#include <string>

std::string loadStringFromSysFs(const char* fileName);

int loadIntFromSysFs(const char* fileName);

#endif //SYSFS_H
