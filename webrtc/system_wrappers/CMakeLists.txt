cmake_minimum_required(VERSION 2.6)
project(system_wrappers)

include_directories(./source)
include_directories(./interface)
file(GLOB lib_src ./source/*.cc ./interface/*.cc)

add_library(system_wrappers STATIC ${lib_src})