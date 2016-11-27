#include "GameState.hpp"

#include "Window.hpp"
#include "Input.hpp"
#include "Events.hpp"
#include "EntityFactory.hpp"
#include "TransformComponent.hpp"
#include "LightComponent.hpp"


void GameState::Start() {
    State::Start();

    EntityFactory::CreatePlayer();
    EntityFactory::CreateMonster(1, 0, -3);
    EntityFactory::CreateFloor();
    EntityFactory::CreateFloor(1, 0, 0);
    EntityFactory::CreateFloor(1, 0, -1);
    EntityFactory::CreateFloor(1, 0, -2);
    EntityFactory::CreateFloor(1, 0, -3);
    EntityFactory::CreateFloor(0, 0, -1);
    EntityFactory::CreateFloor(0, 0, -2);
    EntityFactory::CreateFloor(0, 0, -3);
    EntityFactory::CreateWall(1, -1, 0, 0);
    EntityFactory::CreateWall(2, -1, 0, -1);
    EntityFactory::CreateWall(3, -1, 0, -2);
    EntityFactory::CreateWall(2, -1, 0, -3);

    auto light = Entity::Create();
    light->AttachComponent(std::make_shared<TransformComponent>(1.6f, 2.f, -1.f));
    light->AttachComponent(std::make_shared<LightComponent>(1, 1, 1, 5));
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
