cmake_minimum_required(VERSION 2.6)
project(voice_engine)

include_directories(./.)
file(GLOB file_src ./*.cc)

add_library(voice_engine STATIC ${file_src})
