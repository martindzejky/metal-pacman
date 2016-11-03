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

    auto projection = glm::perspective(glm::radians(45.), (double) width / height, .1, 100.);
    ShaderProgram::Get("Main")->Uniform(ShaderProgram::ProjectionUniformName, projection);

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
    ShaderProgram::Get("Main")->Uniform(ShaderProgram::ViewUniformName, inverse);
}
