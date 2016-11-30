#include "PlayerMoveComponent.hpp"

#include "Entity.hpp"
#include "Input.hpp"
#include "TransformComponent.hpp"


void PlayerMoveComponent::OnAttach(std::weak_ptr<Entity> entity) {
    Component::OnAttach(entity);
    mEntity = entity;

    listenerId = Events::GetSingleton()->AddListener("Update", [this](void *_) { Move(); });
}

void PlayerMoveComponent::OnDetach() {
    Component::OnDetach();
    Events::GetSingleton()->RemoveListener("Update", listenerId);
}

std::string PlayerMoveComponent::GetType() const {
    return "PlayerMoveComponent";
}

void PlayerMoveComponent::Move() {
    auto transform = (TransformComponent *) mEntity.lock()->GetComponent("TransformComponent").get();
    auto input = Input::GetSingleton();
    auto limit = .2f;
    auto speed = .1f;

    if (std::abs(mRotationBuffer) < .00001f) {
        transform->Move(0, 0, -speed);

        if (Input::IsKeyPressed(Input::Key::A)) {
            mRotationBuffer += 3.14f / 2;
        }
        if (Input::IsKeyPressed(Input::Key::D)) {
            mRotationBuffer -= 3.14f / 2;
        }
    }
    else {
        auto rotation = std::min(limit, std::max(-limit, mRotationBuffer));
        mRotationBuffer -= rotation;
        transform->Yaw(rotation);
    }
}
