#ifndef SYSFS_H
#define SYSFS_H

#include <string>

std::string loadStringFromSysFs(const std::string &fileName);

int loadIntFromSysFs(const std::string &fileName);

#endif //SYSFS_H
