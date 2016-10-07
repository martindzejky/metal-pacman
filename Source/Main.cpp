#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "ArrayObject.hpp"
#include "BufferObject.hpp"
#include "Shader.hpp"
#include "ShaderProgram.hpp"
#include "Transform.hpp"


int main() {

    // init GLFW
    glfwSetErrorCallback([](int error, const char *description) {
        std::cerr << "GLFW error " << error << ": " << description << std::endl;
    });

    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        exit(EXIT_FAILURE);
    }

    // create window
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    auto window = glfwCreateWindow(600, 600, "Cross Them Lights", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create a window\n";
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    // setup OpenGL
    // glEnable(GL_CULL_FACE);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    //glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // init GLEW
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW\n";
        glfwDestroyWindow(window);
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    // cube arrays
//    float size = 100.f;
//    GLfloat vertexArray[] = {
//        -size, -size, -size,
//        -size, -size, size,
//        -size, size, size,
//        -size, size, -size,
//        size, -size, -size,
//        size, -size, size,
//        size, size, size,
//        size, size, -size
//    };
//    GLfloat colorArray[] = {
//        0.f, 0.f, 0.f,
//        1.f, 0.f, 0.f,
//        1.f, 1.f, 0.f,
//        0.f, 1.f, 0.f,
//        0.f, 0.f, 1.f,
//        1.f, 0.f, 1.f,
//        1.f, 1.f, 1.f,
//        0.f, 1.f, 1.f
//    };
//    GLubyte indexArray[] = {
//        0, 1, 2,
//        0, 2, 3,
//        4, 6, 5,
//        4, 7, 6,
//        1, 5, 6,
//        1, 6, 2,
//        0, 3, 7,
//        0, 7, 4,
//        0, 4, 5,
//        0, 5, 1,
//        2, 6, 7,
//        2, 7, 3
//    };
    const GLfloat vertexArray[] = {
        -100.f, -100.f, -100.f,
        100.f, -100.f, -100.f,
        100.f, 100.f, -100.f,
        -100.f, 100.f, -100.f
    };
    const GLfloat colorArray[] = {
        1.f, 0.f, 0.f,
        1.f, 1.f, 0.f,
        0.f, 1.f, 0.f,
        0.f, 0.f, 1.f
    };
    const GLuint indexArray[] = {
        0, 1, 2,
        0, 2, 3
    };

    // array object
    ArrayObject ao;
    ao.Bind();

    // buffer objects
    BufferObject vertices(BufferObject::Type::Vertex);
    vertices.CopyData(sizeof(vertexArray), (void *) vertexArray);

    BufferObject colors(BufferObject::Type::Vertex);
    colors.CopyData(sizeof(colorArray), (void *) colorArray);

    BufferObject indices(BufferObject::Type::Index);
    indices.CopyData(sizeof(indexArray), (void *) indexArray);

    // shaders
    Shader vertexShader("Shaders/Vertex.glsl", Shader::Type::Vertex);
    Shader fragmentShader("Shaders/Fragment.glsl", Shader::Type::Fragment);

    ShaderProgram program;
    program.Add(vertexShader.GetId());
    program.Add(fragmentShader.GetId());
    program.Link("oColor");
    program.Use();

    vertices.Bind();
    program.Attribute("iPosition", 3);
    colors.Bind();
    program.Attribute("iColor", 3);

    // camera
    Transform camera(0.f, 0.f, 200.f);

    // main loop
    while (!glfwWindowShouldClose(window)) {
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        glViewport(0, 0, width, height);

        auto projection = glm::perspective(glm::radians(45.f), (float) width / height, .1f, 1000.f);
        program.Uniform("uProjection", projection);

        // update view
        auto view = camera.GetMatrix();
        auto inverse = glm::inverse(view);
        program.Uniform("uView", inverse);

        // check the ESC key
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, true);
        }

        // clear
        glClearColor(0, 0, 0, 0);
        glClear(GL_COLOR_BUFFER_BIT);

        // draw
        indices.Bind();
//        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // swap
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    exit(0);

}
