#ifndef SPOTIFY_H
#define SPOTIFY_H

#include <string>
#include "ModuleInterface.h"
#include "SpotifyDBusInterface.h"

class Spotify : public ModuleInterface
{
public:
    Spotify();
    ~Spotify() = default;

    std::string getOutput() final;

private:
    DBus::BusDispatcher dispatcher;
    SpotifyDBusInterface* spotify;
};

#endif //SPOTIFY_H
