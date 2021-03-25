cmake_minimum_required(VERSION 2.8)

project(waybar-tools)

file(GLOB src "src/*.cpp")
file(GLOB modules "src/modules/*.cpp")

add_subdirectory("thirdparty/libdbus-c++")
add_executable(waybar-tools ${src} ${modules} ${libdbus-c++})

target_include_directories(waybar-tools PRIVATE "include/")
target_include_directories(waybar-tools PRIVATE "thirdparty/libdbus-c++/include")
target_include_directories(waybar-tools PRIVATE "/usr/include/dbus-1.0")
target_include_directories(waybar-tools PRIVATE "/usr/lib/x86_64-linux-gnu/dbus-1.0/include/")

target_link_libraries(waybar-tools libdbus-c++ -ldbus-1)

target_compile_options(waybar-tools PRIVATE -Wall -Wpedantic -Wextra -Werror)
