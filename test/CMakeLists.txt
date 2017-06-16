find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_library(GameObjectTest GameObjectTest.cpp)
add_library(HitboxTest HitboxTest.cpp)
add_library(MissileLauncherTest MissileLauncherTest.cpp)
add_library(CollisionDetectorTest CollisionDetectorTest.cpp)
add_library(GameStateHandlertest GameStateHandlertest.cpp)
add_library(KeyboardListenerTest KeyboardListenerTest.cpp)
add_library(UniverseTest UniverseTest.cpp)

add_executable(runTests TestAll.cpp)
target_link_libraries(runTests ${GTEST_LIBRARIES} ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES} pthread GameObjectTest HitboxTest MissileLauncherTest CollisionDetectorTest GameStateHandlertest KeyboardListenerTest UniverseTest)

