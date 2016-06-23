cmake_minimum_required(VERSION 2.6)
project(talk_app)

include_directories(./../../)
include_directories(./webrtc)
file(GLOB app_src ./webrtc/*.cc)

add_library(talk_app STATIC ${app_src})