#include "GameState.hpp"

#include "Window.hpp"
#include "Input.hpp"
#include "Entity.hpp"
#include "TransformComponent.hpp"
#include "CameraComponent.hpp"
#include "PlayerComponent.hpp"
#include "ModelComponent.hpp"
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

    auto chair = Entity::Create();
    auto chairTransform = std::make_shared<TransformComponent>(2.7f, 0.45f, -4.f);
    chairTransform->Pitch(-3.14f / 2.f);
    chairTransform->Yaw(3.14f / 2.f, Transform::Space::Global);
    chair->AttachComponent(chairTransform);
    chair->AttachComponent(std::make_shared<ModelComponent>("ChairModel", "WoodDiffuseTexture",
                                                            "WoodNormalTexture", "WoodReflectionTexture"));

    auto chair2 = Entity::Create();
    auto chair2Transform = std::make_shared<TransformComponent>(1.4f, 0.24f, 7.4f);
    chair2Transform->Yaw(2.5f, Transform::Space::Global);
    chair2->AttachComponent(chair2Transform);
    chair2->AttachComponent(std::make_shared<ModelComponent>("ChairModel", "WoodDiffuseTexture",
                                                            "WoodNormalTexture", "WoodReflectionTexture"));

    auto light = Entity::Create();
    light->AttachComponent(std::make_shared<TransformComponent>(1.f, 2.f, -4.f));
    light->AttachComponent(std::make_shared<LightComponent>(.9f, .7f, .4f, 12));

    auto light2 = Entity::Create();
    light2->AttachComponent(std::make_shared<TransformComponent>(-2.f, .8f, 8.f));
    light2->AttachComponent(std::make_shared<LightComponent>(.1f, .5f, .9f, 9));

    auto bucket = Entity::Create();
    auto bucketTransform = std::make_shared<TransformComponent>(1.1f, 0.2f, -6.1f);
    bucketTransform->Pitch(-3.14f / 2.f);
    bucket->AttachComponent(bucketTransform);
    bucket->AttachComponent(std::make_shared<ModelComponent>("BucketModel", "DarkWoodDiffuseTexture",
                                                            "DarkWoodNormalTexture", "DarkWoodReflectionTexture"));
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
