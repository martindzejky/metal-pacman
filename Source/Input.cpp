#include "Input.hpp"

#include <GLFW/glfw3.h>

#include "Window.hpp"
#include "Events.hpp"


void Input::Create() {
    auto singleton = std::make_shared<Input>();
    SetSingleton(singleton);

    glfwGetCursorPos(Window::GetSingleton()->mGlfwWindow, &(singleton->mLastMouseX), &(singleton->mLastMouseY));
    glfwSetCursorPosCallback(Window::GetSingleton()->mGlfwWindow, OnMouseMoved);
    glfwSetInputMode(Window::GetSingleton()->mGlfwWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    Events::GetSingleton()->AddListener("PostUpdate", [](void *) {
        GetSingleton()->mMouseDeltaX = 0;
        GetSingleton()->mMouseDeltaY = 0;
    });
}

void Input::ToggleMode() {
    mMouseLocked = !mMouseLocked;
    if (mMouseLocked) {
        glfwSetInputMode(Window::GetSingleton()->mGlfwWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }
    else {
        glfwSetInputMode(Window::GetSingleton()->mGlfwWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
}

void Input::OnMouseMoved(GLFWwindow *_, double x, double y) {
    auto singleton = GetSingleton();

    singleton->mMouseDeltaX = x - singleton->mLastMouseX;
    singleton->mMouseDeltaY = y - singleton->mLastMouseY;
    singleton->mLastMouseX = x;
    singleton->mLastMouseY = y;
}

bool Input::IsKeyPressed(Key key) {
    return glfwGetKey(Window::GetSingleton()->mGlfwWindow, (int) key) == GLFW_PRESS;
}

bool Input::IsButtonPressed(Input::Button button) {
    return glfwGetMouseButton(Window::GetSingleton()->mGlfwWindow, (int) button) == GLFW_PRESS;
}

const bool &Input::IsMouseLocked() const {
    return mMouseLocked;
}

const double &Input::GetMouseDeltaX() const {
    return mMouseDeltaX;
}

const double &Input::GetMouseDeltaY() const {
    return mMouseDeltaY;
}

SINGLETON_DEFINE(Input);
