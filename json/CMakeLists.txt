cmake_minimum_required(VERSION 2.6)
project(json_app)

include_directories(./../)
file(GLOB json_src ./*.cpp)

add_library(json_app STATIC ${json_src})
