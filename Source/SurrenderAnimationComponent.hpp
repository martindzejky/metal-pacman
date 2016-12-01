#pragma once

#include "Component.hpp"
#include "Transform.hpp"
#include "Events.hpp"


/**
 * Makes the monster surrender when the time comes.
 */


class SurrenderAnimationComponent : public Component {

public:

    virtual std::string GetType() const override;

    void Surrender();

    SurrenderAnimationComponent(std::shared_ptr<Entity> leftArm, std::shared_ptr<Entity> rightArm);


private:

    std::shared_ptr<Entity> mLeftArm;
    std::shared_ptr<Entity> mRightArm;

};


