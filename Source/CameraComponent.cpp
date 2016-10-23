#include "CameraComponent.hpp"

#include <glm/matrix.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Window.hpp"
#include "ShaderProgram.hpp"


void CameraComponent::OnAttach(std::weak_ptr<Entity> entity) {
    Component::OnAttach(entity);

    int width, height;
    Window::GetSingleton()->GetSize(width, height);

    auto projection = glm::perspective(glm::radians(45.f), (float) width / height, .1f, 1000.f);
    mShaderProgram->Uniform("uProjection", projection);
}

std::string CameraComponent::GetType() const {
    return "CameraComponent";
}

CameraComponent::CameraComponent(std::shared_ptr<ShaderProgram> shaderProgram)
    : mShaderProgram(shaderProgram) {
}
