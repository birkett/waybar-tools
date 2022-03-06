#ifndef SPOTIFY_DBUS_INTERFACE_H
#define SPOTIFY_DBUS_INTERFACE_H

#include <string>

#include "dbus.h"

class SpotifyDBusInterface
{
public:
    SpotifyDBusInterface() : connection(new DBus::Connection()) {}
    ~SpotifyDBusInterface();

    [[nodiscard]] std::string PlaybackStatus() const;
    [[nodiscard]] std::map<std::string, DBus::Variant> Metadata() const;

private:
    [[nodiscard]] DBus::Variant getProperty(const std::string &propertyName) const;
    DBus::Connection* connection;
};

#endif //SPOTIFY_DBUS_INTERFACE_H
