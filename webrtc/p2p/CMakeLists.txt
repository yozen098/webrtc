cmake_minimum_required(VERSION 2.6)
project(p2p)

#include_directories(./base)
#include_directories(./client)
#include_directories(./stunprober)
include_directories(./../../)

file(GLOB lib_src ./base/*.cc)

add_library(p2p STATIC ${lib_src})

