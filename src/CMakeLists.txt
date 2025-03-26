set(BALLROLLER_SOURCE_FILES
        Gameloop.cpp
        Gameloop.hpp
        PhysicsEngine.cpp
        PhysicsEngine.hpp
)

cmake_minimum_required(VERSION 3.28)
project(BallRollerLib LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.0.0
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM)
FetchContent_MakeAvailable(SFML)

FetchContent_Declare(box2d
        GIT_REPOSITORY https://github.com/erincatto/box2d.git
        GIT_TAG v3.0.0
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM)
FetchContent_MakeAvailable(box2d)


add_library(BallRollerLib STATIC ${BALLROLLER_SOURCE_FILES})
target_include_directories(BallRollerLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_compile_features(BallRollerLib PRIVATE cxx_std_17)
target_link_libraries(BallRollerLib PRIVATE SFML::Graphics)
target_link_libraries(BallRollerLib PRIVATE box2d)
