#pragma once

#include "Component.hpp"
#include "Events.hpp"


/**
 * When attached to an entity, camera uses the transform to update
 * view matrix.
 * TODO: Add tests
 */


class ShaderProgram;
class Entity;

class CameraComponent : public Component {

public:

    virtual void OnAttach(std::weak_ptr<Entity> entity) override;
    virtual void OnDetach() override;
    virtual std::string GetType() const override;

    void OnUpdate();

    CameraComponent(std::shared_ptr<ShaderProgram> shaderProgram);


private:

    std::shared_ptr<ShaderProgram> mShaderProgram;
    std::weak_ptr<Entity> mEntity;
    Events::ListenerId listenerId;

};


