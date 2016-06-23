cmake_minimum_required(VERSION 2.6)
project(audio_device)

include_directories(./)
include_directories(./include)
file(GLOB lib_src ./*.cc)
if (UNIX)
  include_directories(./linux)
  file(GLOB platform_src ./linux)
elseif (ANDROID)
  include_directories(./android)
  file(GLOB platform_src ./android)
endif ()


add_library(audio_device STATIC ${lib_src} ${platform_src})