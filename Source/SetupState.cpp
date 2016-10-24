#include "SetupState.hpp"

#include "Window.hpp"
#include "LoadState.hpp"
#include "Events.hpp"
#include "Input.hpp"
#include "Resources.hpp"


void SetupState::Start() {
    State::Start();

    Window::Create(1200, 800, "Cross Them Lights");
    Events::Create();
    Resources::Create();
    Input::Create();

    SwitchInto(std::make_shared<LoadState>());
}
