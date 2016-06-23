cmake_minimum_required(VERSION 2.6)
project(sound)

include_directories(./)
file(GLOB lib_src ./*.cc)

add_library(sound STATIC ${lib_src})