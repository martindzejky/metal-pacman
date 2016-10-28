#include "PlayerComponent.hpp"

#include "Entity.hpp"
#include "Input.hpp"
#include "TransformComponent.hpp"


void PlayerComponent::OnAttach(std::weak_ptr<Entity> entity) {
    Component::OnAttach(entity);
    mEntity = entity;

    listenerId = Events::GetSingleton()->AddListener("Update", [this](void *) { Move(); });
}

void PlayerComponent::OnDetach() {
    Component::OnDetach();
    Events::GetSingleton()->RemoveListener("Update", listenerId);
}

std::string PlayerComponent::GetType() const {
    return "PlayerComponent";
}

void PlayerComponent::Move() {
    auto transform = (TransformComponent *) mEntity.lock()->GetComponent("TransformComponent").get();
    auto input = Input::GetSingleton();
    auto speed = 2.f;
    auto look = .01f;
    auto mouseLook = .002f;

    // toggle lock
    if (Input::IsButtonPressed(Input::Button::Right)) {
        if (!mPreviousMousePressed) {
            mPreviousMousePressed = true;
            input->ToggleMode();
        }
    }
    else {
        mPreviousMousePressed = false;
    }

    // sprint
    if (Input::IsKeyPressed(Input::Key::LeftShift)) {
        speed *= 4;
    }

    // movement
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

    // keyboard looking
    if (Input::IsKeyPressed(Input::Key::Up)) {
        transform->Pitch(look);
    }
    if (Input::IsKeyPressed(Input::Key::Down)) {
        transform->Pitch(-look);
    }
    if (Input::IsKeyPressed(Input::Key::Left)) {
        transform->Yaw(look, Transform::Space::Global);
    }
    if (Input::IsKeyPressed(Input::Key::Right)) {
        transform->Yaw(-look, Transform::Space::Global);
    }

    // mouse looking
    if (input->IsMouseLocked()) {
        transform->Yaw(-mouseLook * (float) input->GetMouseDeltaX(), Transform::Space::Global);
        transform->Pitch(-mouseLook * (float) input->GetMouseDeltaY());
    }
}
