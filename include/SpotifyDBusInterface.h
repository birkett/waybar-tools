#ifndef SPOTIFY_DBUS_INTERFACE_H
#define SPOTIFY_DBUS_INTERFACE_H

#include <string>

#include "dbus.h"

class SpotifyDBusInterface : public DBus::Object
{
public:
    SpotifyDBusInterface(const std::string &path, const std::string &name) : DBus::Object(path, name) {}
    std::string PlaybackStatus() const;
    std::map<std::string, DBus::Variant> Metadata() const;

private:
    DBus::Variant getProperty(const std::string &propertyName) const;
};

#endif //SPOTIFY_DBUS_INTERFACE_H
