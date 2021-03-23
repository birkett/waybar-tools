#ifndef SPOTIFY_DBUS_INTERFACE_H
#define SPOTIFY_DBUS_INTERFACE_H

#include <dbus-c++-1/dbus-c++/dbus.h>
#include "../doc/SpotifyProxy.h"

#define PLAYER_INTERFACE_NAME "org.mpris.MediaPlayer2.Player"

//class Player_proxy : public DBus::InterfaceProxy
//{
//public:
//    Player_proxy() : DBus::InterfaceProxy(PLAYER_INTERFACE_NAME) {}
//};

class SpotifyDBusInterface : public DBus::ObjectProxy, public DBus::IntrospectableProxy, public org::mpris::MediaPlayer2::Player_proxy
{
public:
    SpotifyDBusInterface(DBus::Connection& connection, const char* path, const char* name)
            : DBus::ObjectProxy(connection, path, name) {
    }

    void Seeked(const int64_t& Position);

    std::string PlaybackStatus2();
//    std::map<std::string, DBus::Variant> Metadata();
//    int64_t Position();

//private:
//    DBus::Variant getProperty(const char* propertyName);
};

#endif //SPOTIFY_DBUS_INTERFACE_H
