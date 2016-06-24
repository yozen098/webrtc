cmake_minimum_required(VERSION 2.6)
project(talk_media)

include_directories(/usr/include/gtk-2.0)
include_directories(/usr/include/glib-2.0)
include_directories(/usr/lib/x86_64-linux-gnu/glib-2.0/include)
include_directories(./../../)
include_directories(./devices)
file(GLOB media_src ./devices/devicemanager.cc ./devices/dummydevicemanager.cc)

add_library(talk_media_devices STATIC ${media_src})


file(GLOB tm_base_src ./base/codec.cc)
add_library(talk_media_base STATIC ${tm_base_src})
