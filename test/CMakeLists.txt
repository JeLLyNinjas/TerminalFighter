# We need thread support
find_package(Threads REQUIRED)

# Enable ExternalProject CMake module
include(ExternalProject)

# Download and install GoogleTest
ExternalProject_Add(
    gtest
    URL https://github.com/google/googletest/archive/master.zip
    PREFIX ${CMAKE_CURRENT_BINARY_DIR}/gtest
    # Disable install step
    INSTALL_COMMAND ""
    )

# Get GTest source and binary directories from CMake project
ExternalProject_Get_Property(gtest source_dir binary_dir)

# Create a libgtest target to be used as a dependency by test programs
add_library(libgtest IMPORTED STATIC GLOBAL)
add_dependencies(libgtest gtest)

# Set libgtest properties
set_target_properties(libgtest PROPERTIES
    "IMPORTED_LOCATION" "${binary_dir}/googlemock/gtest/libgtest.a"
    "IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
    )

# Create a libgmock target to be used as a dependency by test programs
add_library(libgmock IMPORTED STATIC GLOBAL)
add_dependencies(libgmock gtest)

# Set libgmock properties
set_target_properties(libgmock PROPERTIES
    "IMPORTED_LOCATION" "${binary_dir}/googlemock/libgmock.a"
    "IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
    )

# I couldn't make it work with INTERFACE_INCLUDE_DIRECTORIES
include_directories("${source_dir}/googletest/include"
    "${source_dir}/googlemock/include")

#from http://www.kaizou.org/2014/11/gtest-cmake/

add_library(GameObjectTest GameObjectTest.cpp)
add_library(HitboxTest HitboxTest.cpp)
add_library(MissileLauncherTest MissileLauncherTest.cpp)
add_library(CollisionDetectorTest CollisionDetectorTest.cpp)
add_library(GameStateHandlertest GameStateHandlertest.cpp)
add_library(KeyboardListenerTest KeyboardListenerTest.cpp)
add_library(UniverseTest UniverseTest.cpp)
add_library(TerminalListenerTest TerminalListenerTest.cpp)

target_link_libraries(GameObjectTest libgtest libgmock GameObject Hitbox)
target_link_libraries(HitboxTest libgtest libgmock Hitbox)
target_link_libraries(MissileLauncherTest libgtest libgmock MissileLauncher Missile)
target_link_libraries(CollisionDetectorTest libgtest libgmock CollisionDetector)
target_link_libraries(GameStateHandlertest libgtest libgmock GamestateHandler)
target_link_libraries(KeyboardListenerTest libgtest libgmock ${SDL2_LIBRARIES} MissileLauncher Keyboard Events)
target_link_libraries(UniverseTest libgtest libgmock ${SDL2_LIBRARIES} Universe)
target_link_libraries(TerminalListenerTest libgtest libgmock ${SDL2_LIBRARIES} ${SDL2_TTF_LIBRARIES} Terminal)

add_executable(runTests TestAll.cpp)
target_link_libraries(runTests libgtest libgmock ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES}
    pthread GameObjectTest HitboxTest MissileLauncherTest CollisionDetectorTest GameStateHandlertest
    KeyboardListenerTest UniverseTest TerminalListenerTest)

