#include "SurrenderAnimationComponent.hpp"

#include "TransformComponent.hpp"
#include "Entity.hpp"


std::string SurrenderAnimationComponent::GetType() const {
    return "SurrenderAnimationComponent";
}

void SurrenderAnimationComponent::Surrender() {
    mLeftArm->DetachComponent("MonsterArmAnimationComponent");
    auto leftTransform = (TransformComponent *) mLeftArm->GetComponent("TransformComponent").get();
    leftTransform->SetRotation(0, -1.4f, 0);

    mRightArm->DetachComponent("MonsterArmAnimationComponent");
    auto rightTransform = (TransformComponent *) mRightArm->GetComponent("TransformComponent").get();
    rightTransform->SetRotation(0, 1.4f, 0);
}

SurrenderAnimationComponent::SurrenderAnimationComponent(std::shared_ptr<Entity> leftArm,
                                                         std::shared_ptr<Entity> rightArm)
    : mLeftArm(leftArm), mRightArm(rightArm) {}
