include_directories(${CMAKE_SOURCE_DIR}/src/)
include_directories(${CMAKE_SOURCE_DIR}/src/Engine/)
include_directories(${CMAKE_SOURCE_DIR}/src/TerminalFighter/)

add_library(BasicEnemy BasicEnemy/BasicEnemy.cpp)
add_library(MainCharacter MainCharacter/MainCharacter.cpp)
add_library(Missile Missile/Missile.cpp)
add_library(MissileLauncher MissileLauncher/MissileLauncher.cpp)
add_library(Terminal Terminal/Terminal.cpp)
add_library(TargetingSystem TargetingSystem/TargetingSystem.cpp)
add_library(MenuState MenuState/MenuState.cpp)
add_library(TestState TestState/TestState.cpp)
add_library(Settings Settings/Settings.cpp)
add_library(MainMenu MainMenu/MainMenu.cpp)
add_library(TextArea TextArea/TextArea.cpp)

target_link_libraries(BasicEnemy Hitbox)
target_link_libraries(MainCharacter ${SDL2_LIBRARIES})
target_link_libraries(Missile ${SDL2_LIBRARIES} GraphicsHandler glog::glog)
target_link_libraries(MissileLauncher Missile GameObjectMediator TargetingSystem Util)
target_link_libraries(Terminal ${SDL2_LIBRARIES} ${SDL2_TTF_LIBRARIES} GameObject Hitbox GraphicsHandler)
target_link_libraries(TestState GameObjectMediator Universe CollisionDetector BasicEnemy
GraphicsHandler MainCharacter MissileLauncher Events Delay Keyboard Terminal TargetingSystem AudioHandler Settings)
target_link_libraries(Settings yaml-cpp)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} glog::glog ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES}
    ${SDL2_TTF_LIBRARIES} ${SDL2_MIXER_LIBRARIES} TestState MenuState GameStateHandler MainMenu TextArea)
