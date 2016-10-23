#pragma once

#include "State.hpp"


/**
 * This is the first state. It creates the window and sets
 * everything up.
 */


class SetupState : public State {

public:

    virtual void Start() override;
    virtual void Update(float deltaSeconds) override {};

};


