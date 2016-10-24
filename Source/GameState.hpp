#pragma once

#include "State.hpp"


/**
 * The main game state. Runs the game, renders frames, updates the logic, yadi yada.
 */


class Entity;
class ShaderProgram;
// TODO: Remove
class ArrayObject;
class BufferObject;
class Transform;

class GameState : public State {

public:

    virtual void Start() override;
    virtual void Update(float deltaSeconds) override;

    GameState(std::shared_ptr<ShaderProgram> shaderProgram);


private:

    std::shared_ptr<ShaderProgram> mShaderProgram;

    std::shared_ptr<Entity> mCamera;
    std::shared_ptr<Entity> mCube;

    // TODO: Remove
    std::shared_ptr<ArrayObject> ao2;
    std::shared_ptr<BufferObject> vertices2;
    std::shared_ptr<BufferObject> colors2;
    std::shared_ptr<BufferObject> indices2;
    std::shared_ptr<Transform> transform2;

};


