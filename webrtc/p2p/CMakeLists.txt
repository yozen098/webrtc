cmake_minimum_required(VERSION 2.6)
project(p2p)

include_directories(./base)
include_directories(./client)
include_directories(./stunprober)

file(GLOG lib_src ./base/*.cc ./client/*.cc ./stunprober/*.cc)

add_library(${CMAKE_PROJECT_NAME} STATIC ${lib_src})