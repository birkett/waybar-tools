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

    [[nodiscard]] bool isPlaying() const
    {
        return this->status == "Playing";
    }

    [[nodiscard]] bool isPaused() const
    {
        return this->status == "Paused";
    }

    [[nodiscard]] bool isStopped() const
    {
        return this->status == "Stopped";
    }

    [[nodiscard]] bool hasArtist() const
    {
        return this->artist.length() > 0;
    }

    [[nodiscard]] bool hasAlbum() const
    {
        return this->album.length() > 0;
    }

    [[nodiscard]] bool hasTitle() const
    {
        return this->title.length() > 0;
    }

    [[nodiscard]] std::string toString() const
    {
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
    ~Spotify() override;

    std::string getOutput() final;
    unsigned short getRefreshTimeMs() final;

private:
    static std::string getIcons(const SpotifyMeta &meta);

    SpotifyDBusInterface* spotify;
};

#endif //SPOTIFY_H
