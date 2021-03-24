cmake_minimum_required(VERSION 2.8)

project(libdbus-c++)

file(GLOB src "src/*.cpp")

add_library(libdbus-c++ SHARED ${src})

target_include_directories(libdbus-c++ PRIVATE "include/")
target_include_directories(libdbus-c++ PRIVATE "/usr/include/dbus-1.0")
target_include_directories(libdbus-c++ PRIVATE "/usr/lib/x86_64-linux-gnu/dbus-1.0/include/")

target_link_libraries(libdbus-c++ PRIVATE -lpthread -ldbus-1)

target_compile_options(libdbus-c++ PRIVATE -Wall -Wpedantic -Wextra)
