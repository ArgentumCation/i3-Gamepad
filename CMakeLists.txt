cmake_minimum_required(VERSION 3.10)

project(i3-gamepad VERSION 0.1)

add_executable(i3-gamepad main.cxx)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_library(XDO_LIB xdo)
TARGET_LINK_LIBRARIES(i3-gamepad PRIVATE "${XDO_LIB}")
