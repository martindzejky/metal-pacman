#include "TransformComponent.hpp"


std::string TransformComponent::GetType() const {
    return "TransformComponent";
}

TransformComponent::TransformComponent(float x, float y, float z)
    : Transform(x, y, z) {
}

TransformComponent::TransformComponent(glm::vec3 pos)
    : Transform(pos) {
}
