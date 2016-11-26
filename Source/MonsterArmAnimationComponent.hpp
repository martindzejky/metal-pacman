#pragma once

#include "Component.hpp"
#include "Transform.hpp"
#include "Events.hpp"


/**
 * This component takes care of the Monster arms animation.
 */


class MonsterArmAnimationComponent : public Component {

public:

    virtual void OnAttach(std::weak_ptr<Entity> entity) override;
    virtual void OnDetach() override;
    virtual std::string GetType() const override;

    void OnUpdate(float deltaSeconds);


private:

    std::weak_ptr<Entity> mEntity;
    Events::ListenerId listenerId;

    float mProgress = 0;

};


