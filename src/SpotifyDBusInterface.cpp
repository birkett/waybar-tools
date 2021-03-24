#include "SpotifyDBusInterface.h"

std::string Player_proxy::PlaybackStatus()
{
    return this->getProperty("PlaybackStatus");
}

std::map<std::string, DBus::Variant> Player_proxy::Metadata()
{
    return this->getProperty("Metadata");
}

DBus::Variant Player_proxy::getProperty(const char *propertyName)
{
    DBus::CallMessage call;
    call.member("Get");
    call.interface("org.freedesktop.DBus.Properties");

    DBus::MessageIter wi = call.writer();

    wi << std::string(PLAYER_INTERFACE_NAME) << std::string(propertyName);

    DBus::Message ret = this->invoke_method(call);

    DBus::MessageIter ri = ret.reader();
    DBus::Variant out;
    ri >> out;

    return out;
}
