#include "PacmanAnimationComponent.hpp"

#include "TransformComponent.hpp"
#include "Entity.hpp"


void PacmanAnimationComponent::OnAttach(std::weak_ptr<Entity> entity) {
    Component::OnAttach(entity);
    mEntity = entity;

    listenerId = Events::GetSingleton()->AddListener("Update", [this](void *deltaSeconds) {
        OnUpdate(*((float *) deltaSeconds));
    });
}

void PacmanAnimationComponent::OnDetach() {
    Component::OnDetach();
    Events::GetSingleton()->RemoveListener("Update", listenerId);
}

std::string PacmanAnimationComponent::GetType() const {
    return "PacmanAnimationComponent";
}

void PacmanAnimationComponent::OnUpdate(float deltaSeconds) {
    mProgress += deltaSeconds;
    auto transform = (TransformComponent *) mEntity.lock()->GetComponent("TransformComponent").get();

    transform->SetPosition(0, .12f + std::sin(mProgress * 20) * .12f, 0);
}
