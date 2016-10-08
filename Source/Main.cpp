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


void MoveCamera(GLFWwindow *window, Transform &camera) {
    // camera movement
    float speed = 2.f;

    auto d = glfwGetKey(window, GLFW_KEY_D);
    if (d == GLFW_PRESS)
        camera.Move(speed, 0.f, 0.f);
    auto a = glfwGetKey(window, GLFW_KEY_A);
    if (a == GLFW_PRESS)
        camera.Move(-speed, 0.f, 0.f);

    auto w = glfwGetKey(window, GLFW_KEY_W);
    if (w == GLFW_PRESS)
        camera.Move(0.f, 0.f, -speed);
    auto s = glfwGetKey(window, GLFW_KEY_S);
    if (s == GLFW_PRESS)
        camera.Move(0.f, 0.f, speed);

    auto shift = glfwGetKey(window, GLFW_KEY_LEFT_SHIFT);
    if (shift == GLFW_PRESS)
        camera.Move(0.f, speed, 0.f, Transform::Space::Global);
    auto ctrl = glfwGetKey(window, GLFW_KEY_LEFT_CONTROL);
    if (ctrl == GLFW_PRESS)
        camera.Move(0.f, -speed, 0.f, Transform::Space::Global);

    // camera looking
    float looking = .01f;

    auto left = glfwGetKey(window, GLFW_KEY_LEFT);
    if (left == GLFW_PRESS)
        camera.Yaw(looking, Transform::Space::Global);
    auto right = glfwGetKey(window, GLFW_KEY_RIGHT);
    if (right == GLFW_PRESS)
        camera.Yaw(-looking, Transform::Space::Global);

    auto up = glfwGetKey(window, GLFW_KEY_UP);
    if (up == GLFW_PRESS)
        camera.Pitch(looking);
    auto down = glfwGetKey(window, GLFW_KEY_DOWN);
    if (down == GLFW_PRESS)
        camera.Pitch(-looking);
}

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

    auto window = glfwCreateWindow(1200, 800, "Cross Them Lights", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create a window\n";
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    // setup OpenGL
    glEnable(GL_CULL_FACE);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // init GLEW
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW\n";
        glfwDestroyWindow(window);
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    // cube arrays
    float size = 40.f;
    GLfloat vertexArray[] = {
        -size, -size, -size,
        -size, -size, size,
        -size, size, size,
        -size, size, -size,
        size, -size, -size,
        size, -size, size,
        size, size, size,
        size, size, -size
    };
    GLfloat colorArray[] = {
        0.f, 0.f, 0.f,
        1.f, 0.f, 0.f,
        1.f, 1.f, 0.f,
        0.f, 1.f, 0.f,
        0.f, 0.f, 1.f,
        1.f, 0.f, 1.f,
        1.f, 1.f, 1.f,
        0.f, 1.f, 1.f
    };
    GLuint indexArray[] = {
        0, 1, 2,
        0, 2, 3,
        4, 6, 5,
        4, 7, 6,
        1, 5, 6,
        1, 6, 2,
        0, 3, 7,
        0, 7, 4,
        0, 4, 5,
        0, 5, 1,
        2, 6, 7,
        2, 7, 3
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
        // check the ESC key
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, true);
        }
        MoveCamera(window, camera);

        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        glViewport(0, 0, width, height);

        auto projection = glm::perspective(glm::radians(45.f), (float) width / height, .1f, 1000.f);
        program.Uniform("uProjection", projection);

        // update view
        auto view = camera.GetMatrix();
        auto inverse = glm::inverse(view);
        program.Uniform("uView", inverse);

        // clear
        glClearColor(0, 0, 0, 0);
        glClear(GL_COLOR_BUFFER_BIT);

        // draw
        indices.Bind();
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        // swap
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    exit(0);

}
