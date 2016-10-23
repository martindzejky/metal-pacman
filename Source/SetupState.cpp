#include "SetupState.hpp"

#include "Window.hpp"
#include "Events.hpp"
#include "LoadState.hpp"


void SetupState::Start() {
    State::Start();

    Window::Create(1200, 800, "Cross Them Lights");
    Events::Create();
    SwitchInto(std::make_shared<LoadState>());
}
