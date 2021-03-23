#ifndef SPOTIFY_H
#define SPOTIFY_H

#include <string>
#include "ModuleInterface.h"
#include "SpotifyDBusInterface.h"

class Spotify : public ModuleInterface
{
public:
    Spotify() = default;
    ~Spotify() = default;

    std::string getOutput() final;
};

#endif //SPOTIFY_H
