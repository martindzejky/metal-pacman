#include "Window.hpp"

#include <sstream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Error.hpp"


std::shared_ptr<Window> Window::Create(unsigned int width, unsigned int height, std::string title, bool fullscreen) {
    if (Window::GetSingleton()) {
        THROW_ERROR("One window already exists");
    }

    Window* window = new Window();

    // init GLFW
    glfwSetErrorCallback([](int error, const char *description) {
        std::stringstream ss;
        ss << "GLFW error " << error << ": " << description;
        THROW_ERROR(ss.str());
    });

    if (!glfwInit()) {
        THROW_ERROR("Failed to initialize GLFW");
    }

    // create window
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window->mGlfwWindow = glfwCreateWindow(width, height, title.c_str(),
                                        fullscreen ? glfwGetPrimaryMonitor() : NULL, NULL);
    if (!window->mGlfwWindow) {
        THROW_ERROR("Failed to create a window");
    }

    glfwMakeContextCurrent(window->mGlfwWindow);
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
        THROW_ERROR("Failed to initialize GLEW");
    }

    std::shared_ptr<Window> ptr(window);
    SetSingleton(ptr);
    return ptr;
}

void Window::SwapBuffers() {
    glfwSwapBuffers(mGlfwWindow);
}

void Window::PollEvents() {
    glfwPollEvents();
}

void Window::Close() {
    glfwSetWindowShouldClose(mGlfwWindow, true);
}

void Window::GetSize(int &width, int &height) const {
    glfwGetFramebufferSize(mGlfwWindow, &width, &height);
}

bool Window::IsClosed() const {
    return (bool) glfwWindowShouldClose(mGlfwWindow);
}

GLFWwindow *Window::GetInternalPtr() const {
    return mGlfwWindow;
}

Window::~Window() {
    glfwDestroyWindow(mGlfwWindow);
    glfwTerminate();
}

SINGLETON_DEFINE(Window);
