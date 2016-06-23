project(webrtc_engine)
cmake_minimum_required(VERSION 2.6)

set(WEBRTC_OUT webrtc_engine)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

set(PATH_WEBRTC ./webrtc)
set(PATH_TALK ./talk)
set(PATH_JSON ./json)

add_subdirectory(${PATH_WEBRTC})
#add_subdirectory(${PATH_TALK})
#add_subdirectory(${PATH_JSON})

add_subdirectory(p2pvideo)
