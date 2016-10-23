#include "Window.hpp"

#include <sstream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Error.hpp"


std::shared_ptr<Window> Window::Create(unsigned int width, unsigned int height, std::string title, bool fullscreen) {
    if (Window::GetSingleton()) {
        THROW_ERROR("One window already exists");
    }

    PreInit();

    std::shared_ptr<Window> window(new Window());
    window->mGlfwWindow = glfwCreateWindow(width, height, title.c_str(),
                                           fullscreen ? glfwGetPrimaryMonitor() : NULL, NULL);

    PostInit(window->mGlfwWindow);

    SetSingleton(window);
    return window;
}

std::shared_ptr<Window> Window::CreateHidden() {
    if (Window::GetSingleton()) {
        THROW_ERROR("One window already exists");
    }

    PreInit();

    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
    std::shared_ptr<Window> window(new Window());
    window->mGlfwWindow = glfwCreateWindow(400, 300, "", NULL, NULL);

    PostInit(window->mGlfwWindow);

    SetSingleton(window);
    return window;
}

void Window::Destroy() {
    SetSingleton(std::shared_ptr<Window>());
}

void Window::UpdateViewport() {
    int width, height;
    GetSize(width, height);
    glViewport(0, 0, width, height);
}

void Window::Clear() {
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);
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

Window::~Window() {
    glfwDestroyWindow(mGlfwWindow);
    glfwTerminate();
}

void Window::PreInit() {
    glfwSetErrorCallback([](int error, const char *description) {
        std::stringstream ss;
        ss << "GLFW error " << error << ": " << description;
        THROW_ERROR(ss.str());
    });

    if (!glfwInit()) {
        THROW_ERROR("Failed to initialize GLFW");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void Window::PostInit(GLFWwindow *window) {
    if (!window) {
        THROW_ERROR("Failed to create a window");
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    glEnable(GL_CULL_FACE);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        THROW_ERROR("Failed to initialize GLEW");
    }
}

SINGLETON_DEFINE(Window);
