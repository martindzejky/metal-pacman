#include "MovingComponent.hpp"

#include "TransformComponent.hpp"
#include "Entity.hpp"


void MovingComponent::OnAttach(std::weak_ptr<Entity> entity) {
    Component::OnAttach(entity);
    mEntity = entity;

    listenerId = Events::GetSingleton()->AddListener("Update", [this](void *deltaSeconds) {
        OnUpdate(*((float *) deltaSeconds));
    });
}

void MovingComponent::OnDetach() {
    Component::OnDetach();
    Events::GetSingleton()->RemoveListener("Update", listenerId);
}

std::string MovingComponent::GetType() const {
    return "MovingComponent";
}

void MovingComponent::OnUpdate(float deltaSeconds) {
    auto transform = (TransformComponent *) mEntity.lock()->GetComponent("TransformComponent").get();

    switch (mAxis) {
        case Transform::Axis::X:
            transform->Move(mSpeed, 0, 0, mSpace);
            break;

        case Transform::Axis::Y:
            transform->Move(0, mSpeed, 0, mSpace);
            break;

        case Transform::Axis::Z:
            transform->Move(0, 0, mSpeed, mSpace);
            break;
    }
}

MovingComponent::MovingComponent(Transform::Axis axis, float speed, Transform::Space space)
    : mAxis(axis), mSpeed(speed), mSpace(space) {
}
