cmake_minimum_required(VERSION 2.6)
project(audio_coding)

include_directories(./codecs)
file(GLOB lib_src ./codecs/*.cc)

add_library(audio_coding STATIC ${lib_src})