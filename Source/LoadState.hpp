#pragma once

#include "State.hpp"


/**
 * The state loads all resources and enters the game.
 */


class LoadState : public State {

public:

    virtual void Start() override;
    virtual void Update(float deltaSeconds) override {};

};


