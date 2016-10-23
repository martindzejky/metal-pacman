#pragma once

#include "Component.hpp"


/**
 * When attached to an entity, camera uses the transform to update
 * view matrix.
 */


class ShaderProgram;

class CameraComponent : public Component {

public:

    virtual void OnAttach(std::weak_ptr<Entity> entity) override;
    virtual std::string GetType() const override;

    CameraComponent(std::shared_ptr<ShaderProgram> shaderProgram);


private:

    std::shared_ptr<ShaderProgram> mShaderProgram;

};


