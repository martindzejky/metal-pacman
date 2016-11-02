#include "GameState.hpp"

#include "Window.hpp"
#include "Input.hpp"
#include "Entity.hpp"
#include "TransformComponent.hpp"
#include "CameraComponent.hpp"
#include "PlayerComponent.hpp"
#include "ModelComponent.hpp"
#include "ColorCubeComponent.hpp"
#include "RotatingComponent.hpp"


void GameState::Start() {
    State::Start();

    auto camera = Entity::Create();
    camera->AttachComponent(std::make_shared<TransformComponent>(0, 1.7f, 0));
    camera->AttachComponent(std::make_shared<CameraComponent>());
    camera->AttachComponent(std::make_shared<PlayerComponent>());

    auto level = Entity::Create();
    auto levelTransform = std::make_shared<TransformComponent>();
    levelTransform->Pitch(-3.14f / 2.f);
    level->AttachComponent(levelTransform);
    level->AttachComponent(std::make_shared<ModelComponent>("RoomModel", "CobbleDiffuseTexture",
                                                            "CobbleNormalTexture", "CobbleReflectionTexture"));

    auto table = Entity::Create();
    auto tableTransform = std::make_shared<TransformComponent>(2.7f, 0.72f, -5.f);
    tableTransform->Pitch(-3.14f / 2.f);
    table->AttachComponent(tableTransform);
    table->AttachComponent(std::make_shared<ModelComponent>("TableModel", "WoodDiffuseTexture",
                                                            "WoodNormalTexture", "WoodReflectionTexture"));
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
