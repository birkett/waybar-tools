#include "modules/Spotify.h"

Spotify::Spotify()
{
    DBus::default_dispatcher = &this->dispatcher;
    DBus::Connection bus = DBus::Connection::SessionBus();

    this->spotify = new SpotifyDBusInterface(bus, "/org/mpris/MediaPlayer2", "org.mpris.MediaPlayer2.spotify");
}

std::string Spotify::getOutput()
{
    std::string status = spotify->PlaybackStatus();
    std::string artist;
    std::string album;
    std::string title;
    std::string output;

    bool isPlaying = status == "Playing";
    bool isPaused = status == "Paused";
    bool isStopped = status == "Stopped";

    for (auto const& item : spotify->Metadata())
    {
        if (item.first == "xesam:artist") {
            artist = item.second.reader().recurse().get_string();
        }

        if (item.first == "xesam:album") {
            album = item.second.reader().get_string();
        }

        if (item.first == "xesam:title") {
            title = item.second.reader().get_string();
        }
    }

    output.append("\uF1BC "); // Spotify icon.

    if (isStopped) {
        output.append("\uF04D "); // Stopped icon.

        return output;
    }

    if (isPlaying) {
        output.append("\uF04B "); // Play icon.
    }

    if (isPaused) {
        output.append("\uF28B "); // Pause icon.
    }

    if (artist.length() > 0) {
        output.append(artist);
    }

    if (album.length() > 0) {
        output.append(" - ");
        output.append(album);
    }

    if (title.length() > 0) {
        output.append(" - ");
        output.append(title);
    }

    return output;
}
