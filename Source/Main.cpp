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
#include "Window.hpp"


int main() {

    auto window = Window::Create(1200, 800, "Cross Them Lights");

    // shaders
    Shader vertexShader("Shaders/Vertex.glsl", Shader::Type::Vertex);
    Shader fragmentShader("Shaders/Fragment.glsl", Shader::Type::Fragment);

    ShaderProgram program;
    program.Add(vertexShader.GetId());
    program.Add(fragmentShader.GetId());
    program.Link("oColor");
    program.Use();


    // main loop
    while (!window->IsClosed()) {
        // check the ESC key
        if (glfwGetKey(window->GetInternalPtr(), GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            window->Close();
        }

        int width, height;
        window->GetSize(width, height);
        glViewport(0, 0, width, height);

        // clear
        glClearColor(0, 0, 0, 0);
        glClear(GL_COLOR_BUFFER_BIT);

        // swap
        window->SwapBuffers();
        window->PollEvents();
    }

}
