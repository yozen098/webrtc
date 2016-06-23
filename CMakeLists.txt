project(webrtc_engine)
cmake_minimum_required(VERSION 2.6)

set(WEBRTC_OUT webrtc_engine)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

set(PATH_WEBRTC ./webrtc)
set(PATH_TALK ./talk)
set(PATH_JSON ./json)

add_subdirectory(${PATH_WEBRTC})
add_subdirectory(${PATH_TALK})
add_subdirectory(${PATH_JSON})

set(PLATFORM_SPECIFIC_DEFINITIONS 
	-DWEBRTC_POSIX
	-DWEBRTC_LINUX
)

add_definitions(
	${PLATFORM_SPECIFIC_DEFINITIONS}
	-std=gnu++11
	-ldl
	-lss3
	-lrt
	-DEXPAT_RELATIVE_PATH
	#-DSSL_USE_NSS
	-DSSL_USE_SCHANNEL
	-DWEBRTC_LOGGING=1
)

#add_library(${WEBRTC_OUT} SHARED ${WEBRTC_HEADERS} ${WEBRTC_SOURCES})

#target_link_libraries(${WEBRTC_OUT} ${PLATFORM_SPECIFIC_DEFINITIONS})

add_subdirectory(p2pvideo)
