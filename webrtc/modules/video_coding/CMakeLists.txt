cmake_minimum_required(VERSION 2.6)
project(video_coding)

include_directories(./codecs/h264)
include_directories(./codecs/h264/include)
file(GLOB h264_src ./codecs/h264/*.cc)
add_library(h264 STATIC ${h264_src})


include_directories(./codecs/i420/main/interface)
include_directories(./codecs/i420/main/source)
file(GLOB i420_src ./codecs/i420/main/source/*.cc)
add_library(i420 STATIC ${i420_src})

include_directories(./codecs/interface)
include_directories(./codecs/mock)

add_library(video_coding_tool STATIC ./codecs/tools/video_quality_measurement.cc)

include_directories(./codecs/vp8)
include_directories(./codecs/vp8/include)
file(GLOB vp8_src ./codecs/vp8/*.cc)
add_library(vp8 STATIC ${vp8_src})

include_directories(./codecs/vp9)
include_directories(./codecs/vp9/include)
file(GLOB vp9_src ./codecs/vp9/*.cc)
add_library(vp9 STATIC ${vp9_src})

#include_directories()
