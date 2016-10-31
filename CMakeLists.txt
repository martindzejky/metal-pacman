project(CrossThemLights)


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
    Source/ColorCubeComponent.cpp
    Source/Component.cpp
    Source/Entity.cpp
    Source/Error.cpp
    Source/Events.cpp
    Source/GameState.cpp
    Source/Input.cpp
    Source/LoadState.cpp
    Source/ModelComponent.cpp
    Source/ModelData.cpp
    Source/PlayerComponent.cpp
    Source/Resources.cpp
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
add_executable(CrossThemLights Source/Main.cpp ${SOURCE_FILES})
target_link_libraries(CrossThemLights ${CONAN_LIBS} ${OPENGL_LIBRARY})

# compile & link tests
add_executable(CrossThemLightsTests ${TEST_FILES} ${SOURCE_FILES})
target_link_libraries(CrossThemLightsTests ${CONAN_LIBS} ${OPENGL_LIBRARY})
