cmake_minimum_required(VERSION 3.20)

project(DiscoveryCameraGUI LANGUAGES C)
set(CMAKE_C_STANDARD 99)

message(STATUS "Build Type: ${CMAKE_BUILD_TYPE}, Flags: ${CMAKE_C_FLAGS}")

add_subdirectory(src)