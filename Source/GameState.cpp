#include "GameState.hpp"

#include "Window.hpp"
#include "Input.hpp"
#include "Entity.hpp"
#include "ShaderProgram.hpp"
#include "TransformComponent.hpp"
#include "CameraComponent.hpp"
#include "PlayerComponent.hpp"
#include "ColorCubeComponent.hpp"


void GameState::Start() {
    State::Start();

    mCamera = Entity::Create();
    mCamera->AttachComponent(std::make_shared<TransformComponent>(0, 0, 200));
    mCamera->AttachComponent(std::make_shared<CameraComponent>(mShaderProgram));
    mCamera->AttachComponent(std::make_shared<PlayerComponent>());

    mCube = Entity::Create();
    mCube->AttachComponent(std::make_shared<TransformComponent>());
    mCube->AttachComponent(std::make_shared<ColorCubeComponent>(40, mShaderProgram));
}

void GameState::Update(float deltaSeconds) {
    auto window = Window::GetSingleton();
    auto events = Events::GetSingleton();

    if (window->IsClosed()) {
        End();
        return;
    }

    if (Input::IsKeyPressed(Input::Key::Escape)) {
        window->Close();
    }

    window->UpdateViewport();
    window->Clear();

    events->FireEvent("Update", &deltaSeconds);
    events->FireEvent("PostUpdate", nullptr);
    events->FireEvent("Render", nullptr);

    window->SwapBuffers();
    window->PollEvents();

}

GameState::GameState(std::shared_ptr<ShaderProgram> shaderProgram)
    : mShaderProgram(shaderProgram) {
}
