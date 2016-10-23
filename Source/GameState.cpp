#include "GameState.hpp"

#include <GLFW/glfw3.h>

#include "Window.hpp"
#include "Entity.hpp"
#include "ShaderProgram.hpp"
#include "TransformComponent.hpp"
#include "CameraComponent.hpp"


void GameState::Start() {
    State::Start();

    mCamera = Entity::Create();
    mCamera->AttachComponent(std::make_shared<TransformComponent>());
    mCamera->AttachComponent(std::make_shared<CameraComponent>(mShaderProgram));
}

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

GameState::GameState(std::shared_ptr<ShaderProgram> shaderProgram) : mShaderProgram(shaderProgram) {
}
