project(MetalPacman)


# meta
cmake_minimum_required(VERSION 3.6)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")


# dependencies
find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIR})
link_directories(${OpenGL_LIBRARY_DIRS})

# conan dependencies
include(conanbuildinfo.cmake)
conan_basic_setup()
set(CMAKE_SKIP_RPATH 0)


# project files
set(SOURCE_FILES
    Libraries/tinyply.cpp
    Source/ArrayObject.cpp
    Source/BufferObject.cpp
    Source/CameraComponent.cpp
    Source/CameraControlComponent.cpp
    Source/ColliderComponent.cpp
    Source/Component.cpp
    Source/Entity.cpp
    Source/EntityFactory.cpp
    Source/Error.cpp
    Source/Events.cpp
    Source/ShadowMap.cpp
    Source/GameState.cpp
    Source/Input.cpp
    Source/LevelLoader.cpp
    Source/LightComponent.cpp
    Source/LoadState.cpp
    Source/ModelComponent.cpp
    Source/ModelData.cpp
    Source/MonsterArmAnimationComponent.cpp
    Source/PacmanAnimationComponent.cpp
    Source/PlayerMoveComponent.cpp
    Source/Resources.cpp
    Source/RotatingComponent.cpp
    Source/SetupState.cpp
    Source/Shader.cpp
    Source/ShaderProgram.cpp
    Source/State.cpp
    Source/Texture.cpp
    Source/TransformComponent.cpp
    Source/Transform.cpp
    Source/Window.cpp
    )

# test files
set(TEST_FILES
    Tests/ArrayObjectTest.cpp
    Tests/BufferObjectTest.cpp
    Tests/EntityTest.cpp
    Tests/ErrorTest.cpp
    Tests/ShaderProgramTest.cpp
    Tests/ShaderTest.cpp
    Tests/SingletonTest.cpp
    Tests/StateTest.cpp
    Tests/WindowTest.cpp
    )


# compile & link project
add_executable(MetalPacman Source/Main.cpp ${SOURCE_FILES})
target_link_libraries(MetalPacman ${CONAN_LIBS} ${OPENGL_LIBRARY})

# compile & link tests
add_executable(MetalPacmanTests ${TEST_FILES} ${SOURCE_FILES})
target_link_libraries(MetalPacmanTests ${CONAN_LIBS} ${OPENGL_LIBRARY})
