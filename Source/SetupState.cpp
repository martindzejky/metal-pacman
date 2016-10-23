#include "SetupState.hpp"

#include "Window.hpp"
#include "LoadState.hpp"


void SetupState::Start() {
    State::Start();

    Window::Create(1200, 800, "Cross Them Lights");
    SwitchInto(std::make_shared<LoadState>());
}
