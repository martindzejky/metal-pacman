#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

#include "ArrayObject.hpp"
#include "BufferObject.hpp"
#include "Shader.hpp"
#include "ShaderProgram.hpp"


/**
 * Initialize OpenGL, GLFW, and make a window.
 */
GLFWwindow *initialize() {

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

    auto window = glfwCreateWindow(600, 600, "OpenGL v3 - GL4, GLFW", NULL, NULL);
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

    return window;

}


/**
 * Clear up resources and terminate.
 */
void terminate(GLFWwindow *window, int exitCode = EXIT_SUCCESS) {

    glfwDestroyWindow(window);
    glfwTerminate();

    exit(exitCode);

}


/**
 * Update the OpenGL viewport based on window size.
 */
void updateViewport(GLFWwindow *window, ShaderProgram &shaderProgram) {

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    auto projection = glm::perspective(glm::radians(45.0f), (float) width / height, .1f, 1000.0f);
    shaderProgram.Uniform("uProjection", projection);

}


/**
 * Bresenham's line drawing algorithm.
 */
void drawLine(std::vector<unsigned char> &buffer, int width, int x1, int y1, int x2, int y2, unsigned char r,
              unsigned char g, unsigned char b) {

    bool steep = abs(x2 - x1) < abs(y2 - y1);
    if (steep) {
        std::swap(x1, y1);
        std::swap(x2, y2);
    }

    if (x1 > x2) {
        std::swap(x1, x2);
        std::swap(y1, y2);
    }

    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int error = 2 * dy - dx;
    int dir = y2 > y1 ? 1 : -1;

    if (dir < 0) {
        --y1;
        --y2;
    }

    for (int y = y1, x = x1; x < x2; ++x) {
        int pixel;
        if (steep)
            pixel = (x * width + y) * 3;
        else
            pixel = (y * width + x) * 3;

        buffer[pixel + 0] = r;
        buffer[pixel + 1] = g;
        buffer[pixel + 2] = b;

        if (error >= 0) {
            y += dir;
            error -= dx;
        }

        error += dy;
    }

}


/**
 * Make the texture – draw on the canvas.
 */
void makeTexture() {

    // create OpenGL texture
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    // configure it
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // make data buffer
    unsigned width = 512;
    unsigned height = 512;
    std::vector<unsigned char> buffer(width * height * 3, 255);

    // draw a star
    int starTips = 5;
    float tipIn = 0.4;
    float tipOut = 0.9;
    float angle = 0;
    float angleMax = 2 * 3.14159265358979f;
    float angleDelta = angleMax / starTips;

    while (angle < angleMax) {
        float newAngle = angle + angleDelta;
        float highAngle = angle + angleDelta / 2;

        drawLine(buffer, width, (int) (std::cos(angle) * tipIn * width / 2 + width / 2),
                 (int) (std::sin(angle) * tipIn * height / 2 + height / 2),
                 (int) (std::cos(highAngle) * tipOut * width / 2 + width / 2),
                 (int) (std::sin(highAngle) * tipOut * height / 2 + height / 2),
                 240, 220, 0);
        drawLine(buffer, width, (int) (std::cos(highAngle) * tipOut * width / 2 + width / 2),
                 (int) (std::sin(highAngle) * tipOut * height / 2 + height / 2),
                 (int) (std::cos(newAngle) * tipIn * width / 2 + width / 2),
                 (int) (std::sin(newAngle) * tipIn * height / 2 + height / 2),
                 240, 220, 0);

        angle = newAngle;
    }

    // load the OpenGL texture
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, buffer.data());

}


/**
 * Entry function.
 */
int main() {

    auto window = initialize();

    // vertices
    const float vertexArray[] = {
        // positions, texture coords
        -1.f, -1.f, 0.f, 1.f,
        1.f, -1.f, 1.f, 1.f,
        1.f, 1.f, 1.f, 0.f,
        -1.f, 1.f, 0.f, 0.f
    };

    // indices
    const int indexArray[] = {
        0, 1, 2,
        0, 2, 3
    };

    // array object
    ArrayObject ao;
    ao.Bind();

    // buffer objects
    BufferObject vertices(BufferObject::Type::Vertex);
    vertices.CopyData(sizeof(vertexArray), (void *) vertexArray);

    BufferObject indices(BufferObject::Type::Index);
    indices.CopyData(sizeof(indexArray), (void *) indexArray);

    makeTexture();

    // shaders
    Shader vertexShader("Shaders/Vertex.glsl", Shader::Type::Vertex);
    Shader fragmentShader("Shaders/Fragment.glsl", Shader::Type::Fragment);

    ShaderProgram program;
    program.Add(vertexShader.GetId());
    program.Add(fragmentShader.GetId());
    program.Link("oColor");
    program.Use();

    program.Attribute("iPosition", 2, 4);
    program.Attribute("iTexcoord", 2, 4, 2);
    program.Texture("uTexture");

    // main loop
    while (!glfwWindowShouldClose(window)) {
        updateViewport(window, program);

        // check the ESC key
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, true);
        }

        // clear
        glClearColor(0, 0, 0, 0);
        glClear(GL_COLOR_BUFFER_BIT);

        // draw
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // swap
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    terminate(window);

}
