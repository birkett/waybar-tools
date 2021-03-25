#ifndef SPOTIFY_H
#define SPOTIFY_H

#include <string>

#include "ModuleInterface.h"
#include "SpotifyDBusInterface.h"

struct SpotifyMeta
{
public:
    std::string status;
    std::string artist;
    std::string album;
    std::string title;

    bool isPlaying() const {
        return this->status == "Playing";
    }

    bool isPaused() const {
        return this->status == "Paused";
    }

    bool isStopped() const {
        return this->status == "Stopped";
    }

    bool hasArtist() const {
        return this->artist.length() > 0;
    }

    bool hasAlbum() const {
        return this->album.length() > 0;
    }

    bool hasTitle() const {
        return this->title.length() > 0;
    }

    std::string toString() const {
        std::string output;

        if (this->hasArtist()) {
            output.append(this->artist);
        }

        if (this->hasAlbum()) {
            output.append(" - ");
            output.append(this->album);
        }

        if (this->hasTitle()) {
            output.append(" - ");
            output.append(this->title);
        }

        return output;
    }
};

class Spotify : public ModuleInterface
{
public:
    Spotify();

    std::string getOutput() final;

private:
    static std::string getIcons(const SpotifyMeta &meta);

    SpotifyDBusInterface* spotify;
};

#endif //SPOTIFY_H
