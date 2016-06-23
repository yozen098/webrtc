cmake_minimum_required(VERSION 2.6)
project(build)

include_directories(./sanitizers)
file(GLOG lib_src ./sanitizers/*.cc)

add_library(${CMAKE_PROJECT_NAME} STATIC ${lib_src})