#include "ColliderComponent.hpp"

#include "Entity.hpp"
#include "TransformComponent.hpp"


void ColliderComponent::OnAttach(std::weak_ptr<Entity> entity) {
    Component::OnAttach(entity);
    mEntity = entity;
}

std::string ColliderComponent::GetType() const {
    return "ColliderComponent";
}

bool ColliderComponent::CheckCollision(int withGroup) const {
    auto entities = Entity::GetAll();
    auto transform = (TransformComponent *) mEntity.lock()->GetComponent("TransformComponent").get();
    auto pos = transform->GetPosition();

    auto myMinX = pos.x - mSize.x;
    auto myMaxX = pos.x + mSize.x;
    auto myMinY = pos.y - mSize.y;
    auto myMaxY = pos.y + mSize.y;
    auto myMinZ = pos.z - mSize.z;
    auto myMaxZ = pos.z + mSize.z;

    for (auto pair : entities) {
        if (pair.first == mEntity.lock()->GetId()) {
            continue;
        }

        auto colliderComponent = pair.second->GetComponent(GetType());
        if (!colliderComponent) {
            continue;
        }

        auto otherCollider = (ColliderComponent *) colliderComponent.get();
        if (((int) otherCollider->mGroup & withGroup) == 0) {
            continue;
        }

        auto otherSize = otherCollider->mSize;
        auto otherTransform = (TransformComponent *) pair.second->GetComponent("TransformComponent").get();
        auto otherPos = otherTransform->GetPosition();

        auto otherMinX = otherPos.x - otherSize.x;
        auto otherMaxX = otherPos.x + otherSize.x;
        auto otherMinY = otherPos.y - otherSize.y;
        auto otherMaxY = otherPos.y + otherSize.y;
        auto otherMinZ = otherPos.z - otherSize.z;
        auto otherMaxZ = otherPos.z + otherSize.z;

        if (myMaxX < otherMinX || otherMaxX < myMinX) {
            continue;
        }
        if (myMaxY < otherMinY || otherMaxY < myMinY) {
            continue;
        }
        if (myMaxZ < otherMinZ || otherMaxZ < myMinZ) {
            continue;
        }

        return true;
    }

    return false;
}

ColliderComponent::ColliderComponent(float sx, float sy, float sz, Group group)
    : mSize(sx, sy, sz), mGroup(group) {}
