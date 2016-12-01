#pragma once

#include "Component.hpp"
#include "Events.hpp"


/**
 * Makes an object collect the collectibles.
 */


class CollectorComponent : public Component {

public:

    virtual void OnAttach(std::weak_ptr<Entity> entity) override;
    virtual void OnDetach() override;
    virtual std::string GetType() const override;

    void OnUpdate();


private:

    std::weak_ptr<Entity> mEntity;
    Events::ListenerId listenerId;

};


