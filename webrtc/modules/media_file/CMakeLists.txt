cmake_minimum_required(VERSION 2.6)
project(media_file)

include_directories(./interface)
include_directories(./source)
file(GLOB lib_src ./source/*.cc)

add_library(media_file STATIC ${lib_src})
