#include "modules/Spotify.h"

Spotify::Spotify()
{
    DBus::default_dispatcher = &this->dispatcher;
    DBus::Connection bus = DBus::Connection::SessionBus();

    this->spotify = new SpotifyDBusInterface(bus, "/org/mpris/MediaPlayer2", "org.mpris.MediaPlayer2.spotify");
}

std::string Spotify::getOutput()
{
    SpotifyMeta metadata;
    std::string output;

    try {
        metadata.status = spotify->PlaybackStatus();

        for (auto const& item : spotify->Metadata())
        {
            if (item.first == "xesam:artist") {
                metadata.artist = item.second.reader().recurse().get_string();
            }

            if (item.first == "xesam:album") {
                metadata.album = item.second.reader().get_string();
            }

            if (item.first == "xesam:title") {
                metadata.title = item.second.reader().get_string();
            }
        }
    } catch (DBus::Error &error) {
        std::cerr << error.message() << std::endl;

        return output;
    }

    output.append(Spotify::getIcons(metadata));
    output.append(metadata.toString());

    return output;
}

std::string Spotify::getIcons(const SpotifyMeta &meta)
{
    std::string output = "\uF1BC "; // Spotify icon.

    if (meta.isStopped()) {
        output.append("\uF04D "); // Stopped icon.
    }

    if (meta.isPlaying()) {
        output.append("\uF04B "); // Play icon.
    }

    if (meta.isPaused()) {
        output.append("\uF28B "); // Pause icon.
    }

    return output;
}
