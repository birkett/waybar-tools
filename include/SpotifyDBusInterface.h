#ifndef SPOTIFY_DBUS_INTERFACE_H
#define SPOTIFY_DBUS_INTERFACE_H

#include "dbus.h"

#define PLAYER_INTERFACE_NAME "org.mpris.MediaPlayer2.Player"

class Player_proxy : public DBus::InterfaceProxy
{
public:
    Player_proxy() : DBus::InterfaceProxy(PLAYER_INTERFACE_NAME) {}

    std::string PlaybackStatus();
    std::map<std::string, DBus::Variant> Metadata();

private:
    DBus::Variant getProperty(const char *propertyName);
};


class SpotifyDBusInterface : public DBus::ObjectProxy, public Player_proxy
{
public:
    SpotifyDBusInterface(DBus::Connection& connection, const char* path, const char* name)
        : DBus::ObjectProxy(connection, path, name) {}
};

#endif //SPOTIFY_DBUS_INTERFACE_H
