#include "SetupState.hpp"


/**
 * Here's where it all starts. Start the game with the first state.
 */


int main() {
    State::Start(std::make_shared<SetupState>());
}
