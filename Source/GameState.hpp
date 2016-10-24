#pragma once

#include "State.hpp"


/**
 * The main game state. Runs the game, renders frames, updates the logic, yadi yada.
 */


class Entity;
class ShaderProgram;

class GameState : public State {

public:

    virtual void Start() override;
    virtual void Update(float deltaSeconds) override;

    GameState(std::shared_ptr<ShaderProgram> shaderProgram);


private:

    std::shared_ptr<ShaderProgram> mShaderProgram;

    std::shared_ptr<Entity> mCamera;
    std::shared_ptr<Entity> mCube;

};


