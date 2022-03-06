#include <dbus.h>

#ifdef DEBUG
    #include <iostream>
#endif

#include "modules/Spotify.h"

Spotify::Spotify()
{
    this->spotify = new SpotifyDBusInterface();
}

Spotify::~Spotify()
{
    delete this->spotify;
}

unsigned short Spotify::getRefreshTimeMs()
{
    return 1000;
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
                metadata.artist = item.second.reader().recurse().getString();
            }

            if (item.first == "xesam:album") {
                metadata.album = item.second.reader().getString();
            }

            if (item.first == "xesam:title") {
                metadata.title = item.second.reader().getString();
            }
        }
    } catch (DBus::Error &error) {
#ifdef DEBUG
        std::cerr << error.message() << std::endl;
#endif
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
