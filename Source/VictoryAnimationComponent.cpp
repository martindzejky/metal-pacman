#include "VictoryAnimationComponent.hpp"

#include "Entity.hpp"
#include "RotatingComponent.hpp"
#include "MovingComponent.hpp"


std::string VictoryAnimationComponent::GetType() const {
    return "VictoryAnimationComponent";
}

void VictoryAnimationComponent::Start() {
    mCameraPivot->DetachComponent("CameraControlComponent");
    mTop->DetachComponent("PacmanAnimationComponent");
    mTopTeeth->DetachComponent("PacmanAnimationComponent");
    mEyes->DetachComponent("PacmanAnimationComponent");

    mCamera->AttachComponent(
        std::make_shared<MovingComponent>(Transform::Axis::Z, .01f));
    mCameraPivot->AttachComponent(
        std::make_shared<RotatingComponent>(Transform::Axis::Y, .3f, Transform::Space::Global));
}

VictoryAnimationComponent::VictoryAnimationComponent(std::shared_ptr<Entity> camera,
                                                     std::shared_ptr<Entity> cameraPivot,
                                                     std::shared_ptr<Entity> top, std::shared_ptr<Entity> topTeeth,
                                                     std::shared_ptr<Entity> eyes)
    : mCamera(camera), mCameraPivot(cameraPivot), mTop(top), mTopTeeth(topTeeth), mEyes(eyes) {}
