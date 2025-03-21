cmake_minimum_required(VERSION 3.28)
project(BallRoller LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(src)
add_executable(BallRoller main.cpp)

target_link_libraries(BallRoller PRIVATE BallRollerLib)
