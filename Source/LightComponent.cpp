#include "LightComponent.hpp"

#include <sstream>

#include "ShaderProgram.hpp"
#include "TransformComponent.hpp"
#include "Entity.hpp"


void LightComponent::OnAttach(std::weak_ptr<Entity> entity) {
    Component::OnAttach(entity);
    mEntity = entity;
    listenerId = Events::GetSingleton()->AddListener("Lights", [this](void *) { OnUpdate(); });

    msLightList.push_back(this);
    auto size = (int) msLightList.size();
    ShaderProgram::GetSingleton()->Uniform(ShaderProgram::LightCountUniformName, size);
}

void LightComponent::OnDetach() {
    Component::OnDetach();
    Events::GetSingleton()->RemoveListener("Lights", listenerId);

    msLightList.remove(this);
    auto size = (int) msLightList.size();
    ShaderProgram::GetSingleton()->Uniform(ShaderProgram::LightCountUniformName, size);
}

std::string LightComponent::GetType() const {
    return "LightComponent";
}

void LightComponent::OnUpdate() {
    auto index = 0;
    for (auto it = msLightList.begin(); it != msLightList.end(); ++it, ++index) {
        if (*it == this) {
            break;
        }
    }

    std::stringstream positions;
    positions << ShaderProgram::LightPositionsUniformName << "[" << index << "]";
    std::stringstream colors;
    colors << ShaderProgram::LightColorsUniformName << "[" << index << "]";
    std::stringstream radiuses;
    radiuses << ShaderProgram::LightRadiusesUniformName << "[" << index << "]";

    auto transform = (TransformComponent *) mEntity.lock()->GetComponent("TransformComponent").get();
    auto position = transform->GetPosition();
    ShaderProgram::GetSingleton()->Uniform(positions.str(), position);
    ShaderProgram::GetSingleton()->Uniform(colors.str(), glm::vec3(mRed, mGreen, mBlue));
    ShaderProgram::GetSingleton()->Uniform(radiuses.str(), mRadius);
}

LightComponent::LightComponent(float r, float g, float b, float radius)
    : mRed(r), mGreen(g), mBlue(b), mRadius(radius) {
}

std::list<LightComponent*> LightComponent::msLightList;
