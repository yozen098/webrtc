cmake_minimum_required(VERSION 2.6)
project(utility)

include_directories(./interface)
include_directories(./interface/mock)
include_directories(./source)
file(GLOB lib_src ./source/*.cc)

add_library(utility STATIC ${lib_src})
