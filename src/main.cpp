#include <chrono>
#include <iostream>
#include <thread>

#include "modules/Battery.h"
#include "modules/Date.h"
#include "modules/Keyboard.h"
#include "modules/Spotify.h"

#ifdef DEBUG
#define MAX_ITERATIONS 2500
void start(ModuleInterface* module)
{
    unsigned int iterations = 0;
    std::chrono::milliseconds delayMs(1);
    auto next = std::chrono::system_clock::now() + delayMs;

    while (true) {
        if (iterations > MAX_ITERATIONS) {
            return;
        }

        std::cout << module->getOutput() << std::endl;

        std::this_thread::sleep_until(next);
        next += delayMs;
        iterations++;
    }
}
#else
[[noreturn]] void start(ModuleInterface* module)
{
    std::chrono::milliseconds delayMs(module->getRefreshTimeMs());
    auto next = std::chrono::system_clock::now() + delayMs;

    while (true) {
        std::cout << module->getOutput() << std::endl;

        std::this_thread::sleep_until(next);
        next += delayMs;
    }
}
#endif

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
