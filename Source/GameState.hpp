#pragma once

#include "State.hpp"


/**
 * The main game state. Runs the game, renders frames, updates the logic, yadi yada.
 */


class GameState : public State {

public:

    virtual void Update(float deltaSeconds) override;

};


