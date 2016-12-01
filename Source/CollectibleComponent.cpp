#include "CollectibleComponent.hpp"

#include "Entity.hpp"
#include "ColliderComponent.hpp"
#include "SurrenderAnimationComponent.hpp"
#include "VictoryAnimationComponent.hpp"


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
        const auto &entities = Entity::GetAll();
        for (auto pair : entities) {
            if (pair.second->GetComponent("MonsterAIComponent")) {
                pair.second->DetachComponent("MonsterAIComponent");

                auto surrender = (SurrenderAnimationComponent *) pair.second->GetComponent(
                    "SurrenderAnimationComponent").get();
                surrender->Surrender();
            }
            else if (pair.second->GetComponent("PlayerMoveComponent")) {
                pair.second->DetachComponent("PlayerMoveComponent");

                auto victory = (VictoryAnimationComponent *) pair.second->GetComponent(
                    "VictoryAnimationComponent").get();
                victory->Start();
            }
        }
    }
}

unsigned int CollectibleComponent::mCount = 0;
