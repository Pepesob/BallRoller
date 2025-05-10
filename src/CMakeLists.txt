set(BALLROLLER_SOURCE_FILES
        Gameloop.cpp
        Gameloop.hpp
        Camera.cpp
        Camera.hpp
        Screen.cpp
        Screen.hpp
        Drawer.hpp
        common.hpp
        AvailableLevelObjects.cpp
        AvailableLevelObjects.hpp
        LevelSetup.cpp
        LevelSetup.hpp
        Level.cpp
        Level.hpp
        simulation/base_drawers/BodyDrawer.cpp
        simulation/base_drawers/BodyDrawer.hpp
        simulation/physics/Simulation.hpp
        simulation/physics/SimulationBody.cpp
        simulation/physics/SimulationBody.hpp
        simulation/physics/Simulation.cpp
        simulation/objects/MainBallObject.hpp
        simulation/objects/MainBallObject.cpp
        simulation/objects/MainBallObject.hpp
        simulation/objects/RectangleObject.cpp
        simulation/objects/RectangleObject.hpp
        simulation/objects/AcceleratorObject.cpp
        simulation/objects/AcceleratorObject.hpp
        simulation/objects/SimulationObjectFactory.cpp
        simulation/objects/SimulationObjectFactory.hpp
        simulation/objects/SimulationObjectBase.hpp
        simulation/objects/GoalObject.cpp
        simulation/objects/GoalObject.hpp
        stage/StateMachine.cpp
        stage/StateMachine.hpp
        stage/ObjectPlacementStage.cpp
        stage/ObjectPlacementStage.hpp
        stage/SimulationStage.cpp
        stage/SimulationStage.hpp
        simulation/objects/BodyCompound.cpp
        simulation/objects/BodyCompound.hpp
        simulation/objects/TeleporterObject.cpp
        simulation/objects/TeleporterObject.hpp
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

FetchContent_Declare(
        yaml-cpp
        GIT_REPOSITORY https://github.com/jbeder/yaml-cpp.git
        GIT_TAG 0.8.0
)
FetchContent_MakeAvailable(yaml-cpp)


add_library(BallRollerLib STATIC ${BALLROLLER_SOURCE_FILES})
target_include_directories(BallRollerLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_compile_features(BallRollerLib PRIVATE cxx_std_17)
target_link_libraries(BallRollerLib PRIVATE SFML::Graphics)
target_link_libraries(BallRollerLib PRIVATE box2d)
target_link_libraries(BallRollerLib PRIVATE yaml-cpp::yaml-cpp)



add_custom_command(TARGET BallRollerLib POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E echo "Copying resources to build directory..."
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/resources"
        "${CMAKE_BINARY_DIR}/resources"
        VERBATIM
)