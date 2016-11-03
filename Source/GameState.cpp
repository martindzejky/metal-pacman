#include "GameState.hpp"

#include "Window.hpp"
#include "Input.hpp"
#include "Entity.hpp"
#include "TransformComponent.hpp"
#include "CameraComponent.hpp"
#include "PlayerComponent.hpp"
#include "ModelComponent.hpp"
#include "ColorCubeComponent.hpp"
#include "LightComponent.hpp"


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
    auto tableTransform = std::make_shared<TransformComponent>(2.7f, 0.68f, -5.f);
    tableTransform->Pitch(-3.14f / 2.f);
    table->AttachComponent(tableTransform);
    table->AttachComponent(std::make_shared<ModelComponent>("TableModel", "WoodDiffuseTexture",
                                                            "WoodNormalTexture", "WoodReflectionTexture"));

    auto table2 = Entity::Create();
    auto table2Transform = std::make_shared<TransformComponent>(-2.4f, 0.68f, 4.4f);
    table2Transform->Pitch(-3.14f / 2.f);
    table2Transform->Yaw(2.f, Transform::Space::Global);
    table2->AttachComponent(table2Transform);
    table2->AttachComponent(std::make_shared<ModelComponent>("TableModel", "WoodDiffuseTexture",
                                                            "WoodNormalTexture", "WoodReflectionTexture"));

    auto light = Entity::Create();
    light->AttachComponent(std::make_shared<TransformComponent>(1.f, 2.f, -4.f));
    light->AttachComponent(std::make_shared<LightComponent>(.9f, .7f, .4f, 12));

    auto light2 = Entity::Create();
    light2->AttachComponent(std::make_shared<TransformComponent>(-2.f, .8f, 8.f));
    light2->AttachComponent(std::make_shared<LightComponent>(.1f, .5f, .9f, 9));
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

    window->Clear();

    events->FireEvent("PreUpdate");
    events->FireEvent("Update", &deltaSeconds);
    events->FireEvent("PostUpdate");

    events->FireEvent("PreRender");
    events->FireEvent("ShadowMaps");

    window->UpdateViewport();
    events->FireEvent("Lights");
    events->FireEvent("Render");
    events->FireEvent("PostRender");

    window->SwapBuffers();
    window->PollEvents();

}

void GameState::End() {
    State::End();

    Entity::DestroyAll();
}
