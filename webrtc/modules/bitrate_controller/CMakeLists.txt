cmake_minimum_required(VERSION 2.6)
project(bitrate_controller)

include_directories(./)
file(GLOB lib_src ./*.cc)

add_library(bitrate_controller STATIC ${lib_src})
