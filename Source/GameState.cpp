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

    auto light = Entity::Create();
    light->AttachComponent(std::make_shared<TransformComponent>(1.4f, 2.f, -2.1f));
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
