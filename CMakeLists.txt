cmake_minimum_required(VERSION 3.28)
project(BallRoller LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(src)
add_executable(BallRoller main.cpp)

message(${MSVC})
if (MSVC AND CMAKE_BUILD_TYPE STREQUAL "Release")
    target_link_options(BallRoller PRIVATE /SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup)
endif()


target_link_libraries(BallRoller PRIVATE BallRollerLib)
