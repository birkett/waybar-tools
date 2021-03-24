cmake_minimum_required(VERSION 2.8)

project(waybar-tools)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wpedantic -Wextra -O0")
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS}")

file(GLOB src "src/*.cpp")
file(GLOB modules "src/modules/*.cpp")
file(GLOB libdbus-c++ "thirdparty/libdbus-c++/src/*.cpp")

add_executable(waybar-tools ${src} ${modules} ${libdbus-c++})

target_include_directories(waybar-tools PRIVATE "include/")
target_include_directories(waybar-tools PRIVATE "thirdparty/libdbus-c++/include")
target_include_directories(waybar-tools PRIVATE "/usr/include/dbus-1.0")
target_include_directories(waybar-tools PRIVATE "/usr/lib/x86_64-linux-gnu/dbus-1.0/include/")

target_link_libraries(waybar-tools -ldbus-1 -lpthread)
