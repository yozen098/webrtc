cmake_minimum_required(VERSION 2.6)
project(remote_bitrate_estimator)

include_directories(./)
include_directories(./include)
include_directories(./tools)
file(GLOB lib_src ./*.cc ./tools/*.cc)

add_library(remote_bitrate_estimator STATIC ${lib_src})
