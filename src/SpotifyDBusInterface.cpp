#include "SpotifyDBusInterface.h"

SpotifyDBusInterface::~SpotifyDBusInterface()
{
    delete this->connection;
}

std::string SpotifyDBusInterface::PlaybackStatus() const
{
    return (std::string)this->getProperty("PlaybackStatus");
}

std::map<std::string, DBus::Variant> SpotifyDBusInterface::Metadata() const
{
    return (std::map<std::string, DBus::Variant>)this->getProperty("Metadata");
}

DBus::Variant SpotifyDBusInterface::getProperty(const std::string &propertyName) const
{
    DBus::CallMessage call(
        "Get",
        "org.freedesktop.DBus.Properties",
        "/org/mpris/MediaPlayer2",
        "org.mpris.MediaPlayer2.spotify"
    );

    DBus::MessageIter wi = call.writer();

    wi << std::string("org.mpris.MediaPlayer2.Player") << propertyName;

    DBus::MessageIter ri = this->connection->sendBlocking(call).reader();
    DBus::Variant out;
    ri >> out;

    return out;
}
