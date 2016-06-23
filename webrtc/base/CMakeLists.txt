cmake_minimum_required(VERSION 2.6)
project(base)

include_directories(./)
file(GLOG lib_src ./*.cc)

add_library(${CMAKE_PROJECT_NAME} STATIC ${lib_src})