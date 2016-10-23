#pragma once

#include "Component.hpp"
#include "Events.hpp"


/**
 * Allows the player to control an entity.
 */


class Entity;

class PlayerComponent : public Component {

public:

    virtual void OnAttach(std::weak_ptr<Entity> entity) override;
    virtual void OnDetach() override;
    virtual std::string GetType() const override;

    void Move();


private:

    std::weak_ptr<Entity> mEntity;
    Events::ListenerId listenerId;

};


