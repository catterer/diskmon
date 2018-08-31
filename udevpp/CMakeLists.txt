cmake_minimum_required(VERSION 3.11)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "-std=c++17 -Wall -g")
project(udevpp)

include_directories(include)
 
set(UDEVPP
    src/udev.cc
    src/monitor.cc
    src/device.cc)

add_library(udevpp ${UDEVPP})
