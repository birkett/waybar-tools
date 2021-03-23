#include <chrono>
#include <iostream>
#include <thread>
#include "modules/Battery.h"
#include "modules/Date.h"
#include "modules/Keyboard.h"
#include "modules/Spotify.h"

bool stop = false;

void start(ModuleInterface* module)
{
    std::chrono::seconds oneSecond(1);
    auto next = std::chrono::system_clock::now() + oneSecond;

    while (!stop) {
        std::cout << module->getOutput() << std::endl;

        std::this_thread::sleep_until(next);
        next += oneSecond;
    }
}

int main (int argc, char** argv)
{
    if (argc < 2) {
        return 0;
    }

    if (std::string(argv[1]) == "battery") {
        start(new Battery());
    }

    if (std::string(argv[1]) == "date") {
        start(new Date());
    }

    if (std::string(argv[1]) == "keyboard") {
        start(new Keyboard());
    }

    if (std::string(argv[1]) == "spotify") {
        start(new Spotify());
    }

    return 0;
}
