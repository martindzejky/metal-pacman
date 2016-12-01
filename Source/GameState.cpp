#include "GameState.hpp"

#include "Window.hpp"
#include "Input.hpp"
#include "Events.hpp"
#include "LevelLoader.hpp"
#include "Entity.hpp"


void GameState::Start() {
    State::Start();

    LevelLoader::Load("Levels/Classic.txt");
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

    Entity::DestroyScheduled();

    if (Input::IsKeyPressed(Input::Key::R)) {
        SwitchInto(std::make_shared<GameState>());
    }
}

void GameState::End() {
    State::End();

    Entity::DestroyAll();
}
