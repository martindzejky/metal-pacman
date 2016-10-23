#include "PlayerComponent.hpp"

#include "Entity.hpp"
#include "Input.hpp"
#include "TransformComponent.hpp"


void PlayerComponent::OnAttach(std::weak_ptr<Entity> entity) {
    Component::OnAttach(entity);
    mEntity = entity;

    Events::GetSingleton()->AddListener("Update", [this](void *) { Move(); });
}

void PlayerComponent::OnDetach() {
    Component::OnDetach();
    Events::GetSingleton()->RemoveListener("Update", listenerId);
}

std::string PlayerComponent::GetType() const {
    return "PlayerComponent";
}

void PlayerComponent::Move() {
    auto transform = (TransformComponent*) mEntity.lock()->GetComponent("TransformComponent").get();
    auto speed = 2.f;

    if (Input::IsKeyPressed(Input::Key::A)) {
        transform->Move(-speed, 0, 0);
    }
    if (Input::IsKeyPressed(Input::Key::D)) {
        transform->Move(speed, 0, 0);
    }
    if (Input::IsKeyPressed(Input::Key::W)) {
        transform->Move(0, 0, -speed);
    }
    if (Input::IsKeyPressed(Input::Key::S)) {
        transform->Move(0, 0, speed);
    }
    if (Input::IsKeyPressed(Input::Key::F)) {
        transform->Move(0, -speed, 0, Transform::Space::Global);
    }
    if (Input::IsKeyPressed(Input::Key::R)) {
        transform->Move(0, speed, 0, Transform::Space::Global);
    }
}
