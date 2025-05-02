set(BALLROLLER_SOURCE_FILES
        Gameloop.cpp
        Gameloop.hpp
        simulation/objects/SimulationObjectBase.hpp
        simulation/objects/MainBallObject.hpp
        simulation/objects/MainBallObject.cpp
        simulation/objects/MainBallObject.hpp
        simulation/objects/RectangleObject.cpp
        simulation/objects/RectangleObject.hpp
        simulation/objects/AcceleratorObject.cpp
        simulation/objects/AcceleratorObject.hpp
        Camera.cpp
        Camera.hpp
        Screen.cpp
        Screen.hpp
        Drawer.cpp
        Drawer.hpp
        common.hpp
        DrawingEngine.cpp
        DrawingEngine.hpp
        ExampleSetup.cpp
        ExampleSetup.hpp
        ObjectPlacementStage.cpp
        ObjectPlacementStage.hpp
        AvailableLevelObjects.cpp
        AvailableLevelObjects.hpp
        simulation/base_drawers/ShapeDrawer.hpp
        simulation/base_drawers/ShapeDrawer.cpp
        simulation/physics/Simulation.hpp
        simulation/physics/SimulationBody.cpp
        simulation/physics/SimulationBody.hpp
        simulation/physics/Simulation.cpp
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
