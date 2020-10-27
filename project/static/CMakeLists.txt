cmake_minimum_required(VERSION 3.9.2)

project(StaticLib)

set (CMAKE_C_STANDARD 99)

set(SOURCES src/utils.c src/find_max.c)
set(HEADERS ../headersutils.h ../headers/find_max.h)
add_library(st_lib STATIC ${SOURCES} ${HEADERS})
target_include_directories(st_lib PUBLIC .)
