cmake_minimum_required(VERSION 2.6)
project(video)

include_directories(./)
file(GLOB lib_src ./*.cc)

add_library(${CMAKE_PROJECT_NAME} STATIC ${lib_src})