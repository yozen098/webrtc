cmake_minimum_required(VERSION 2.6)
project(base)

include_directories(./../../)
file(GLOB lib_src *.cc)

add_library(base STATIC ${lib_src})
