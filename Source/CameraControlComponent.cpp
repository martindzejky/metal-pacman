#include "CameraControlComponent.hpp"

#include "Entity.hpp"
#include "Input.hpp"
#include "TransformComponent.hpp"


void CameraControlComponent::OnAttach(std::weak_ptr<Entity> entity) {
    Component::OnAttach(entity);
    mEntity = entity;

    listenerId = Events::GetSingleton()->AddListener("Update", [this](void *_) { Move(); });
}

void CameraControlComponent::OnDetach() {
    Component::OnDetach();
    Events::GetSingleton()->RemoveListener("Update", listenerId);
}

std::string CameraControlComponent::GetType() const {
    return "CameraControlComponent";
}

void CameraControlComponent::Move() {
    auto transform = (TransformComponent *) mEntity.lock()->GetComponent("TransformComponent").get();
    auto input = Input::GetSingleton();
    auto look = .08f;
    auto mouseLook = .004f;

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
