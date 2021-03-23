cmake_minimum_required(VERSION 2.8)

project(waybar-tools)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wpedantic -Wextra -Werror -O0")
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS}")

file(GLOB src "src/*.cpp")
file(GLOB modules "src/modules/*.cpp")

add_executable(waybar-tools ${src} ${modules})

target_include_directories(waybar-tools PRIVATE "include/")
target_link_libraries(waybar-tools -ldbus-c++-1)
