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

    ModuleInterface* module = nullptr;

    if (std::string(argv[1]) == "battery") {
        module = new Battery();
    }

    if (std::string(argv[1]) == "date") {
        module = new Date();
    }

    if (std::string(argv[1]) == "keyboard") {
        module = new Keyboard();
    }

    if (std::string(argv[1]) == "spotify") {
        module = new Spotify();
    }

    if (module) {
        start(module);
    }

    delete module;

    return 0;
}
