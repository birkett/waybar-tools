#include "SpotifyDBusInterface.h"

std::string SpotifyDBusInterface::PlaybackStatus()
{
    return this->getProperty("PlaybackStatus");
}

std::map<std::string, DBus::Variant> SpotifyDBusInterface::Metadata()
{
    return this->getProperty("Metadata");
}

DBus::Variant SpotifyDBusInterface::getProperty(const char *propertyName)
{
    DBus::CallMessage call;
    call.member("Get");
    call.interface("org.freedesktop.DBus.Properties");

    DBus::MessageIter wi = call.writer();

    wi << std::string("org.mpris.MediaPlayer2.Player") << std::string(propertyName);

    DBus::Message ret = this->invoke_method(call);

    DBus::MessageIter ri = ret.reader();
    DBus::Variant out;
    ri >> out;

    return out;
}
