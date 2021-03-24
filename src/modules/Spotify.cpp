#include "modules/Spotify.h"

Spotify::Spotify()
{
    DBus::default_dispatcher = &this->dispatcher;
    DBus::Connection bus = DBus::Connection::SessionBus();

    this->spotify = new SpotifyDBusInterface(bus, "/org/mpris/MediaPlayer2", "org.mpris.MediaPlayer2.spotify");
}

std::string Spotify::getOutput()
{
    auto meta = spotify->Metadata();

    return spotify->PlaybackStatus();
}
