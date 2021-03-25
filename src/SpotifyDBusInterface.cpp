#include "SpotifyDBusInterface.h"

std::string SpotifyDBusInterface::PlaybackStatus() const
{
    return this->getProperty("PlaybackStatus");
}

std::map<std::string, DBus::Variant> SpotifyDBusInterface::Metadata() const
{
    return this->getProperty("Metadata");
}

DBus::Variant SpotifyDBusInterface::getProperty(const std::string &propertyName) const
{
    DBus::CallMessage call;
    call.member("Get");
    call.interface("org.freedesktop.DBus.Properties");

    DBus::MessageIter wi = call.writer();

    wi << std::string("org.mpris.MediaPlayer2.Player") << propertyName;

    DBus::Message ret = this->invoke_method(call);

    DBus::MessageIter ri = ret.reader();
    DBus::Variant out;
    ri >> out;

    return out;
}
