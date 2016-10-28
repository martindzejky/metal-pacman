#include "GameState.hpp"

#include "Window.hpp"
#include "Input.hpp"
#include "Entity.hpp"
#include "ShaderProgram.hpp"
#include "TransformComponent.hpp"
#include "CameraComponent.hpp"
#include "PlayerComponent.hpp"
#include "ModelComponent.hpp"
#include "ColorCubeComponent.hpp"


void GameState::Start() {
    State::Start();

    auto camera = Entity::Create();
    camera->AttachComponent(std::make_shared<TransformComponent>(0, 0, 200));
    camera->AttachComponent(std::make_shared<CameraComponent>(mShaderProgram));
    camera->AttachComponent(std::make_shared<PlayerComponent>());

    auto model1 = Entity::Create();
    auto transform1 = std::make_shared<TransformComponent>(-100, 0, 0);
    transform1->Scale(40);
    model1->AttachComponent(transform1);
    model1->AttachComponent(std::make_shared<ModelComponent>("Model", mShaderProgram));

    auto model2 = Entity::Create();
    auto transform2 = std::make_shared<TransformComponent>(100, 0, 0);
    transform2->Scale(20);
    model2->AttachComponent(transform2);
    model2->AttachComponent(std::make_shared<ModelComponent>("Hook", mShaderProgram));

    auto cube = Entity::Create();
    cube->AttachComponent(std::make_shared<TransformComponent>());
    cube->AttachComponent(std::make_shared<ColorCubeComponent>(30, mShaderProgram));
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
