cmake_minimum_required(VERSION 3.11)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "-std=c++17 -Wall -g")
project(diskmon)

include_directories(include)
 
set(UDEVPP
    src/udevpp/device.cc)

add_library(udevpp ${UDEVPP})

add_executable(diskmon_tool src/diskmon_tool.cc)
target_link_libraries(diskmon_tool udevpp)
target_link_libraries(diskmon_tool udev)
