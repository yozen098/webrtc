cmake_minimum_required(VERSION 2.6)
project(jingle)

include_directories(./xmllite)
file(GLOB xmllite_src ./xmllite/*.cc)

set(xmllite xmllite)
add_library(${xmllite} STATIC ${xmllite_src})

include_directories(./xmpp)
file(GLOB xmpp_src ./xmpp/*.cc)

set(xmpp xmpp)
add_library(${xmpp} STATIC ${xmpp_src})
