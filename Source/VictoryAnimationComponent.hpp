#pragma once

#include "Component.hpp"
#include "Transform.hpp"
#include "Events.hpp"


/**
 * Makes the player jump in joy.
 */


class VictoryAnimationComponent : public Component {

public:

    virtual std::string GetType() const override;

    void Start();

    VictoryAnimationComponent(std::shared_ptr<Entity> camera, std::shared_ptr<Entity> cameraPivot,
                              std::shared_ptr<Entity> top, std::shared_ptr<Entity> topTeeth,
                              std::shared_ptr<Entity> eyes);


private:

    std::shared_ptr<Entity> mCamera;
    std::shared_ptr<Entity> mCameraPivot;
    std::shared_ptr<Entity> mTop;
    std::shared_ptr<Entity> mTopTeeth;
    std::shared_ptr<Entity> mEyes;

};


