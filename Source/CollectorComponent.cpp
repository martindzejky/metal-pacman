#include "CollectorComponent.hpp"

#include "ColliderComponent.hpp"
#include "Entity.hpp"
#include "GravityComponent.hpp"


void CollectorComponent::OnAttach(std::weak_ptr<Entity> entity) {
    Component::OnAttach(entity);
    mEntity = entity;

    listenerId = Events::GetSingleton()->AddListener("Update", [this](void *_) { OnUpdate(); });
}

void CollectorComponent::OnDetach() {
    Component::OnDetach();
    Events::GetSingleton()->RemoveListener("Update", listenerId);
}

std::string CollectorComponent::GetType() const {
    return "CollectorComponent";
}

void CollectorComponent::OnUpdate() {
    auto collider = (ColliderComponent *) mEntity.lock()->GetComponent("ColliderComponent").get();
    auto collectible = collider->CheckCollision((int) ColliderComponent::Group::Collectible);
    if (collectible) {
        auto entity = Entity::Get(collectible);
        entity->AttachComponent(std::make_shared<GravityComponent>());
        entity->DetachComponent("ColliderComponent");
        entity->DetachComponent("CollectibleComponent");
    }
}
