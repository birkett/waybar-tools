#include "modules/Spotify.h"

std::string Spotify::getOutput()
{
    DBus::BusDispatcher dispatcher;
    DBus::default_dispatcher = &dispatcher;
    DBus::Connection bus = DBus::Connection::SessionBus();

    SpotifyDBusInterface spotify(bus, "/org/mpris/MediaPlayer2", "org.mpris.MediaPlayer2.spotify");

    return spotify.PlaybackStatus();
}
