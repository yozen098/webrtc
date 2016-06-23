cmake_minimum_required(VERSION 2.6)
project(desktop_capture)

include_directories(./)
file(GLOB lib_src ./*.cc)

add_library(desktop_capture STATIC ${lib_src})
