#include "SpotifyDBusInterface.h"

std::string SpotifyDBusInterface::PlaybackStatus2()
{
    return this->PlaybackStatus();
//    return this->getProperty("PlaybackStatus");
}

void SpotifyDBusInterface::Seeked(const int64_t &Position)
{
    if (Position) {
        return;
    }
}

//std::map<std::string, DBus::Variant> SpotifyDBusInterface::Metadata()
//{
//    return this->getProperty("Metadata");
//}
//
//int64_t SpotifyDBusInterface::Position()
//{
//    return this->getProperty("Position");
//}

//DBus::Variant SpotifyDBusInterface::getProperty(const char *propertyName)
//{
//    DBus::CallMessage call;
//
//    call.member("Get");
//    call.interface("org.freedesktop.DBus.Properties");
//
//    DBus::MessageIter wi = call.writer();
//    wi << PLAYER_INTERFACE_NAME;
//    wi << propertyName;
//
//    DBus::Message ret = this->invoke_method(call);
//    DBus::MessageIter ri = ret.reader();
//
//    DBus::Variant out;
//    ri >> out;
//
//    return out;
//}
