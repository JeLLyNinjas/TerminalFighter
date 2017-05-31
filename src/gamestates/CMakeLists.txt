add_library(GamestateHandler GamestateHandler.cpp)
add_library(MenuState MenuState.cpp)
add_library(TestState TestState.cpp)

target_link_libraries(TestState GameObjectMediator Universe CollisionDetector BasicEnemy GraphicsHandler MainCharacter MissileLauncher Events Delay Keyboard)
