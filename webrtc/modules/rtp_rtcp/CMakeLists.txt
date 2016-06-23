cmake_minimum_required(VERSION 2.6)
project(rtp_rtcp)

include_directories(./interface)
include_directories(./mocks)
include_directories(./source)
file(GLOB lib_src ./source/*.cc)

add_library(rtp_rtcp STATIC ${lib_src})
