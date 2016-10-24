#include "CameraComponent.hpp"

#include <glm/matrix.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Window.hpp"
#include "ShaderProgram.hpp"
#include "Entity.hpp"
#include "TransformComponent.hpp"


void CameraComponent::OnAttach(std::weak_ptr<Entity> entity) {
    Component::OnAttach(entity);
    mEntity = entity;

    int width, height;
    Window::GetSingleton()->GetSize(width, height);

    auto projection = glm::perspective(glm::radians(45.f), (float) width / height, .1f, 1000.f);
    mShaderProgram->Uniform("uProjection", projection);

    listenerId = Events::GetSingleton()->AddListener("Update", [this](void *) { OnUpdate(); });
}

void CameraComponent::OnDetach() {
    Component::OnDetach();
    Events::GetSingleton()->RemoveListener("Update", listenerId);
}

std::string CameraComponent::GetType() const {
    return "CameraComponent";
}

void CameraComponent::OnUpdate() {
    auto transform = (TransformComponent*) mEntity.lock()->GetComponent("TransformComponent").get();
    auto view = transform->GetMatrix();
    auto inverse = glm::inverse(view);
    mShaderProgram->Uniform("uView", inverse);
}

CameraComponent::CameraComponent(std::shared_ptr<ShaderProgram> shaderProgram)
    : mShaderProgram(shaderProgram) {
}
