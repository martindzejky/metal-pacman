#include "GameState.hpp"

#include <GLFW/glfw3.h>

#include "Window.hpp"


void GameState::Update(float deltaSeconds) {
    auto window = Window::GetSingleton();
    if (window->IsClosed()) {
        End();
        return;
    }

    // TODO: Make Input class and remove this
    if (glfwGetKey(window->GetInternalPtr(), GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        window->Close();
    }

    window->UpdateViewport();
    window->Clear();

    window->SwapBuffers();
    window->PollEvents();

}
