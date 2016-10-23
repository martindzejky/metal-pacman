#include "GameState.hpp"

#include "Window.hpp"
#include "Input.hpp"
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

    if (Input::IsKeyPressed(Input::Key::Escape)) {
        window->Close();
    }

    window->UpdateViewport();
    window->Clear();

    window->SwapBuffers();
    window->PollEvents();

}

GameState::GameState(std::shared_ptr<ShaderProgram> shaderProgram) : mShaderProgram(shaderProgram) {
}
