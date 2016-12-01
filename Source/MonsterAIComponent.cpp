#include "MonsterAIComponent.hpp"

#include "Entity.hpp"
#include "TransformComponent.hpp"
#include "ColliderComponent.hpp"


void MonsterAIComponent::OnAttach(std::weak_ptr<Entity> entity) {
    Component::OnAttach(entity);
    mEntity = entity;

    listenerId = Events::GetSingleton()->AddListener("Update", [this](void *deltaPtr) { Move(*(float *) deltaPtr); });
}

void MonsterAIComponent::OnDetach() {
    Component::OnDetach();
    Events::GetSingleton()->RemoveListener("Update", listenerId);
}

std::string MonsterAIComponent::GetType() const {
    return "MonsterAIComponent";
}

void MonsterAIComponent::Move(float delta) {
    auto transform = (TransformComponent *) mEntity.lock()->GetComponent("TransformComponent").get();
    auto collider = (ColliderComponent *) mEntity.lock()->GetComponent("ColliderComponent").get();
    auto limit = 4 * delta;
    auto speed = 2.5f * delta;

    if (std::abs(mRotationBuffer) < .00001f) {
        transform->Move(0, 0, speed);
        if (collider->CheckCollision((int) ColliderComponent::Group::Solid)) {
            transform->Move(0, 0, -speed);

            int dir = (dist(re) % 3) - 1;
            mRotationBuffer += 3.14f / 2 * dir;
        }
        else if (collider->CheckCollision((int) ColliderComponent::Group::Hint)) {
            if ((dist(re) % 1000) < 15) {
                int dir = (dist(re) % 3) - 1;
                mRotationBuffer += 3.14f / 2 * dir;
            }
        }
    }
    else {
        auto rotation = std::min(limit, std::max(-limit, mRotationBuffer));
        mRotationBuffer -= rotation;
        transform->Yaw(rotation);
    }
}

std::default_random_engine MonsterAIComponent::re;
std::uniform_int_distribution<int> MonsterAIComponent::dist;
