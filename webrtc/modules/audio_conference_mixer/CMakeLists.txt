cmake_minimum_required(VERSION 2.6)
project(audio_conference_mixer)

include_directories(./interface)
include_directories(./source)
file(GLOB lib_src  ./source/*.cc)

add_library(audio_conference_mixer STATIC ${lib_src})