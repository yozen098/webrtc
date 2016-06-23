cmake_minimum_required(VERSION 2.6)
project(audio_processing)

include_directories(./)
include_directories(./include)
file(GLOB lib_src ./*.cc)

include_directories(./aec)
include_directories(./aec/include)
file(GLOB aec_src ./aec/*.cc)

include_directories(./aecm)
include_directories(./aecm/include)
file(GLOB aecm_src ./aecm/*.cc)

include_directories(./agc)
include_directories(./agc/legacy)
file(GLOB agc_src ./agc/*.cc ./agc/legacy/*.cc)

include_directories(./beamformer)
file(GLOB beamformer_src ./beamformeer/*.cc)

include_directories(./intelligibility)
file(GLOB intelligibility_src ./intelligibility/*.cc)

include_directories(./logging)
file(GLOB logging_src ./logging/*.cc)

include_directories(./ns)
include_directories(./ns/include)
file(GLOB ns_src ./ns/*.cc)

include_directories(./transient)
file(GLOB transient_src ./transient/*.cc)

include_directories(./utility/interface)
include_directories(./utility/interface/mock)
include_directories(./utility/source)
file(GLOB utility_src ./utility/source/*.cc)

include_directories(./vad)
file(GLOB vad_src ./vad/*.cc)



add_library(audio_processing STATIC ${lib_src} ${aec_src} ${aecm_src} ${agc_src} ${beamformer_src} ${intelligibility_src} ${logging_src} ${ns_src} ${transient_src} ${utility_src} ${vad_src})
