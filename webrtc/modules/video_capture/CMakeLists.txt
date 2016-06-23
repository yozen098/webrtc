cmake_minimum_required(VERSION 2.6)
project(video_capture)

include_directories(./)
include_directories(./include)
file(GLOB lib_src ./*.cc)

if (UNIX)
  include_directories(./linux)
  file(GLOB platform_src ./linux)
elseif (ANDROID)
  include_directories(./android)
  file(GLOB platform_src ./android)
elseif (APPLE)
  include_directories(./mac)
  file(GLOB platform_src ./mac)
endif ()


add_library(video_capture STATIC ${lib_src})
