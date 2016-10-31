#include "GameState.hpp"

#include "Window.hpp"
#include "Input.hpp"
#include "Entity.hpp"
#include "TransformComponent.hpp"
#include "CameraComponent.hpp"
#include "PlayerComponent.hpp"
#include "ModelComponent.hpp"
#include "ColorCubeComponent.hpp"


void GameState::Start() {
    State::Start();

    auto camera = Entity::Create();
    camera->AttachComponent(std::make_shared<TransformComponent>(0, 2, 4));
    camera->AttachComponent(std::make_shared<CameraComponent>());
    camera->AttachComponent(std::make_shared<PlayerComponent>());

    auto level = Entity::Create();
    auto levelTransform = std::make_shared<TransformComponent>();
    levelTransform->Pitch(-3.14f / 2.f);
    level->AttachComponent(levelTransform);
    level->AttachComponent(std::make_shared<ModelComponent>("StoneLevel", "CobbleTexture"));

    auto key = Entity::Create();
    auto keyTransform = std::make_shared<TransformComponent>(0, 1, -1);
    keyTransform->Pitch(-3.14f / 2.f);
    keyTransform->Yaw(3.14f / 2.f, Transform::Space::Global);
    keyTransform->Scale(.05f);
    key->AttachComponent(keyTransform);
    key->AttachComponent(std::make_shared<ModelComponent>("Key"));
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
