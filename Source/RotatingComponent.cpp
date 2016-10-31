#include "RotatingComponent.hpp"

#include "TransformComponent.hpp"
#include "Entity.hpp"


void RotatingComponent::OnAttach(std::weak_ptr<Entity> entity) {
    Component::OnAttach(entity);
    mEntity = entity;

    listenerId = Events::GetSingleton()->AddListener("Update", [this](void *) { OnUpdate(); });
}

void RotatingComponent::OnDetach() {
    Component::OnDetach();
    Events::GetSingleton()->RemoveListener("Update", listenerId);
}

std::string RotatingComponent::GetType() const {
    return "RotatingComponent";
}

void RotatingComponent::OnUpdate() {
    auto transform = (TransformComponent *) mEntity.lock()->GetComponent("TransformComponent").get();
    transform->Rotate(mAxis, mSpeed, mSpace);
}

RotatingComponent::RotatingComponent(Transform::Axis axis, float speed, Transform::Space space)
    : mAxis(axis), mSpeed(speed), mSpace(space) {
}
