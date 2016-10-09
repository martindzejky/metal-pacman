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
    Source/ArrayObject.cpp
    Source/BufferObject.cpp
    Source/Component.cpp
    Source/Entity.cpp
    Source/Error.cpp
    Source/Main.cpp
    Source/Shader.cpp
    Source/ShaderProgram.cpp
    Source/Transform.cpp
    )


# compile & link
add_executable(CrossThemLights ${SOURCE_FILES})
target_link_libraries(CrossThemLights ${CONAN_LIBS} ${OPENGL_LIBRARY})
