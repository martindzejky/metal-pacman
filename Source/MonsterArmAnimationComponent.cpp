#include "MonsterArmAnimationComponent.hpp"

#include "TransformComponent.hpp"
#include "Entity.hpp"


void MonsterArmAnimationComponent::OnAttach(std::weak_ptr<Entity> entity) {
    Component::OnAttach(entity);
    mEntity = entity;

    listenerId = Events::GetSingleton()->AddListener("Update", [this](void *deltaSeconds) {
        OnUpdate(*((float *) deltaSeconds));
    });
}

void MonsterArmAnimationComponent::OnDetach() {
    Component::OnDetach();
    Events::GetSingleton()->RemoveListener("Update", listenerId);
}

std::string MonsterArmAnimationComponent::GetType() const {
    return "MonsterArmAnimationComponent";
}

void MonsterArmAnimationComponent::OnUpdate(float deltaSeconds) {
    mProgress += deltaSeconds;
    auto transform = (TransformComponent *) mEntity.lock()->GetComponent("TransformComponent").get();

    transform->SetRotation(0, std::sin(mProgress * 14) * .8f, 0);
}
