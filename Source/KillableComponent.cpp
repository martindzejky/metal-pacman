#include "KillableComponent.hpp"

#include "ColliderComponent.hpp"
#include "GravityComponent.hpp"
#include "TransformComponent.hpp"


void KillableComponent::OnAttach(std::weak_ptr<Entity> entity) {
    Component::OnAttach(entity);
    mEntity = entity;

    listenerId = Events::GetSingleton()->AddListener("Update", [this](void *_) { OnUpdate(); });
}

void KillableComponent::OnDetach() {
    Component::OnDetach();
    Events::GetSingleton()->RemoveListener("Update", listenerId);
}

std::string KillableComponent::GetType() const {
    return "KillableComponent";
}

void KillableComponent::OnUpdate() {
    auto collider = (ColliderComponent *) mEntity.lock()->GetComponent("ColliderComponent").get();
    auto collectible = collider->CheckCollision((int) ColliderComponent::Group::Enemy);
    if (collectible) {
        auto monster = Entity::Get(collectible);
        auto self = mEntity.lock();

        self->ScheduleAttachComponent(std::make_shared<GravityComponent>());
        self->ScheduleDetachComponent("VictoryAnimationComponent");
        self->ScheduleDetachComponent(GetType());
        self->ScheduleDetachComponent("ColliderComponent");
        self->ScheduleDetachComponent("CollectorComponent");
        self->ScheduleDetachComponent("PlayerMoveComponent");

        auto monsterTransform = monster->GetComponent("TransformComponent");
        auto cameraTransform = (TransformComponent *) mCamera->GetComponent("TransformComponent").get();
        cameraTransform->Attach(std::static_pointer_cast<TransformComponent>(monsterTransform));
    }
}

KillableComponent::KillableComponent(std::shared_ptr<Entity> camera) : mCamera(camera) {}
