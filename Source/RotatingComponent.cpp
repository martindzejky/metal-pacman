#include "RotatingComponent.hpp"

#include "TransformComponent.hpp"
#include "Entity.hpp"


void RotatingComponent::OnAttach(std::weak_ptr<Entity> entity) {
    Component::OnAttach(entity);
    mEntity = entity;

    listenerId = Events::GetSingleton()->AddListener("Update", [this](void *deltaSeconds) {
        OnUpdate(*((float *) deltaSeconds));
    });
}

void RotatingComponent::OnDetach() {
    Component::OnDetach();
    Events::GetSingleton()->RemoveListener("Update", listenerId);
}

std::string RotatingComponent::GetType() const {
    return "RotatingComponent";
}

void RotatingComponent::OnUpdate(float deltaSeconds) {
    auto transform = (TransformComponent *) mEntity.lock()->GetComponent("TransformComponent").get();
    transform->Rotate(mAxis, mSpeed * deltaSeconds, mSpace);
}

RotatingComponent::RotatingComponent(Transform::Axis axis, float speed, Transform::Space space)
    : mAxis(axis), mSpeed(speed), mSpace(space) {
}
