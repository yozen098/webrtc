cmake_minimum_required(VERSION 2.6)
project(pacing)

include_directories(./)
include_directories(./include)
file(GLOB lib_src ./*.cc)

add_library(pacing STATIC ${lib_src})
