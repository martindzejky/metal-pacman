#include "PlayerMoveComponent.hpp"

#include "Entity.hpp"
#include "Input.hpp"
#include "TransformComponent.hpp"
#include "ColliderComponent.hpp"


void PlayerMoveComponent::OnAttach(std::weak_ptr<Entity> entity) {
    Component::OnAttach(entity);
    mEntity = entity;

    listenerId = Events::GetSingleton()->AddListener("Update", [this](void *deltaPtr) { Move(*(float *) deltaPtr); });
}

void PlayerMoveComponent::OnDetach() {
    Component::OnDetach();
    Events::GetSingleton()->RemoveListener("Update", listenerId);
}

std::string PlayerMoveComponent::GetType() const {
    return "PlayerMoveComponent";
}

void PlayerMoveComponent::Move(float delta) {
    auto transform = (TransformComponent *) mEntity.lock()->GetComponent("TransformComponent").get();
    auto collider = (ColliderComponent *) mEntity.lock()->GetComponent("ColliderComponent").get();
    auto input = Input::GetSingleton();
    auto limit = 5 * delta;
    auto speed = 3 * delta;

    if (std::abs(mRotationBuffer) < .00001f) {
        transform->Move(0, 0, -speed);
        if (collider->CheckCollision(
            (int) ColliderComponent::Group::Solid | (int) ColliderComponent::Group::FakeSolid)) {
            transform->Move(0, 0, speed);
        }

        if (Input::IsKeyPressed(Input::Key::A)) {
            mRotationBuffer += 3.14f / 2;
        }
        if (Input::IsKeyPressed(Input::Key::D)) {
            mRotationBuffer -= 3.14f / 2;
        }
    }
    else {
        auto pos = transform->GetPosition();
        auto rx = (int) std::round(pos.x * 10) % 10;
        auto rz = (int) std::round(pos.z * 10) % 10;
        if ((rx < 4 || rx > 6) && (rz < 4 || rz > 6)) {
            transform->SetPosition(std::round(pos.x), pos.y, std::round(pos.z));
        }

        auto rotation = std::min(limit, std::max(-limit, mRotationBuffer));
        mRotationBuffer -= rotation;
        transform->Yaw(rotation);
    }
}
