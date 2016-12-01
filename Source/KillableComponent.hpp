#pragma once

#include "Component.hpp"
#include "Events.hpp"


/**
 * Makes an object killable by monsters.
 */


class KillableComponent : public Component {

public:

    virtual void OnAttach(std::weak_ptr<Entity> entity) override;
    virtual void OnDetach() override;
    virtual std::string GetType() const override;

    void OnUpdate();

    KillableComponent(std::shared_ptr<Entity> camera);


private:

    std::weak_ptr<Entity> mEntity;
    std::shared_ptr<Entity> mCamera;
    Events::ListenerId listenerId;

};


