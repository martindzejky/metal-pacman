#include "GravityComponent.hpp"

#include <random>

#include "TransformComponent.hpp"
#include "Entity.hpp"


void GravityComponent::OnAttach(std::weak_ptr<Entity> entity) {
    Component::OnAttach(entity);
    mEntity = entity;

    listenerId = Events::GetSingleton()->AddListener("Update", [this](void *deltaSeconds) {
        OnUpdate(*((float *) deltaSeconds));
    });
}

void GravityComponent::OnDetach() {
    Component::OnDetach();
    Events::GetSingleton()->RemoveListener("Update", listenerId);
}

std::string GravityComponent::GetType() const {
    return "GravityComponent";
}

void GravityComponent::OnUpdate(float deltaSeconds) {
    auto transform = (TransformComponent *) mEntity.lock()->GetComponent("TransformComponent").get();
    transform->Move(0, mSpeed * deltaSeconds, 0, Transform::Space::Global);

    mSpeed -= .7f;

    if (mSpeed < -10) {
        Entity::ScheduleDestroy(mEntity.lock()->GetId());
    }
}
