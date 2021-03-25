#ifndef SPOTIFY_DBUS_INTERFACE_H
#define SPOTIFY_DBUS_INTERFACE_H

#include "dbus.h"

class SpotifyDBusInterface : public DBus::Object
{
public:
    SpotifyDBusInterface(const char* path, const char* name) : DBus::Object(path, name) {}
    std::string PlaybackStatus();
    std::map<std::string, DBus::Variant> Metadata();

private:
    DBus::Variant getProperty(const char *propertyName);
};

#endif //SPOTIFY_DBUS_INTERFACE_H
