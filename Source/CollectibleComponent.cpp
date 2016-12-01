#include "CollectibleComponent.hpp"

#include <iostream>

#include "Entity.hpp"
#include "ColliderComponent.hpp"


void CollectibleComponent::OnAttach(std::weak_ptr<Entity> entity) {
    Component::OnAttach(entity);
    mEntity = entity;
}

std::string CollectibleComponent::GetType() const {
    return "CollectibleComponent";
}

CollectibleComponent::CollectibleComponent() {
    ++mCount;
}

CollectibleComponent::~CollectibleComponent() {
    --mCount;
    if (mCount == 0) {
        std::cout << "OMG YOU WIN!!!\n";
    }
}

unsigned int CollectibleComponent::mCount = 0;
