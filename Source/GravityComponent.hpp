#pragma once

#include "Component.hpp"
#include "Transform.hpp"
#include "Events.hpp"


/**
 * A simple component that makes the entity rotate forever. Configurable.
 */


class GravityComponent : public Component {

public:

    virtual void OnAttach(std::weak_ptr<Entity> entity) override;
    virtual void OnDetach() override;
    virtual std::string GetType() const override;

    void OnUpdate(float deltaSeconds);


private:

    std::weak_ptr<Entity> mEntity;
    Events::ListenerId listenerId;

    float mSpeed = 7;

};


