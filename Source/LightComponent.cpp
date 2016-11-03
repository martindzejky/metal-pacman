#include "LightComponent.hpp"

#include <sstream>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>

#include "ShaderProgram.hpp"
#include "TransformComponent.hpp"
#include "Entity.hpp"
#include "ShadowMap.hpp"
#include "Window.hpp"


void LightComponent::OnAttach(std::weak_ptr<Entity> entity) {
    Component::OnAttach(entity);
    mEntity = entity;
    mUpdateListenerId = Events::GetSingleton()->AddListener("Lights", [this](void *) { OnUpdate(); });
    mShadowsListenerId = Events::GetSingleton()->AddListener("ShadowMaps", [this](void *) { OnShadowMaps(); });

    msLightList.push_back(this);
    auto size = (int) msLightList.size();
    ShaderProgram::Get("Main")->Uniform(ShaderProgram::LightCountUniformName, size);
}

void LightComponent::OnDetach() {
    Component::OnDetach();
    Events::GetSingleton()->RemoveListener("Lights", mUpdateListenerId);
    Events::GetSingleton()->RemoveListener("ShadowMaps", mShadowsListenerId);

    msLightList.remove(this);
    auto size = (int) msLightList.size();
    ShaderProgram::Get("Main")->Uniform(ShaderProgram::LightCountUniformName, size);
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
    std::stringstream spaces;
    spaces << ShaderProgram::LightSpacesUniformName;
    std::stringstream colors;
    colors << ShaderProgram::LightColorsUniformName << "[" << index << "]";
    std::stringstream radiuses;
    radiuses << ShaderProgram::LightRadiusesUniformName << "[" << index << "]";

    auto transform = (TransformComponent *) mEntity.lock()->GetComponent("TransformComponent").get();
    auto position = transform->GetPosition();

    // TODO: Store as a member
    auto projection = glm::perspective(glm::radians(90.f), 1.f, .1f, mRadius);
    auto myTransform = glm::lookAt(position, glm::vec3(2.7f, 0.72f, -5.f), glm::vec3(0, 1, 0));

    ShaderProgram::Get("Main")->Uniform(positions.str(), position);
    ShaderProgram::Get("Main")->Uniform(spaces.str(), projection * myTransform);
    ShaderProgram::Get("Main")->Uniform(colors.str(), glm::vec3(mRed, mGreen, mBlue));
    ShaderProgram::Get("Main")->Uniform(radiuses.str(), mRadius);

    mShadowMap->BindTexture(3);
    ShaderProgram::Get("Main")->Texture(ShaderProgram::ShadowMapsUniformName, 3);
}

void LightComponent::OnShadowMaps() {
    auto transformComponent = (TransformComponent *) mEntity.lock()->GetComponent("TransformComponent").get();
    auto position = transformComponent->GetPosition();

    ShaderProgram::Get("Light")->Use();
    mShadowMap->Bind();
    Window::GetSingleton()->SetViewport(msShadowMapWidth, msShadowMapHeight);
    Window::GetSingleton()->Clear();
    Window::GetSingleton()->CullFront();

    // TODO: Store as a member
    auto projection = glm::perspective(glm::radians(90.f), 1.f, .1f, mRadius);
    auto transform = glm::lookAt(position, glm::vec3(2.7f, 0.72f, -5.f), glm::vec3(0, 1, 0));

    ShaderProgram::Get("Light")->Uniform(ShaderProgram::ProjectionUniformName, projection);
    ShaderProgram::Get("Light")->Uniform(ShaderProgram::ViewUniformName, transform);

    Events::GetSingleton()->FireEvent("RenderShadows");

    mShadowMap->Unbind();
    ShaderProgram::Get("Main")->Use();
    Window::GetSingleton()->CullBack();
}

LightComponent::LightComponent(float r, float g, float b, float radius)
    : mRed(r), mGreen(g), mBlue(b), mRadius(radius) {
    mShadowMap = std::make_shared<ShadowMap>(msShadowMapWidth, msShadowMapHeight);
}

std::list<LightComponent*> LightComponent::msLightList;

const unsigned int LightComponent::msShadowMapWidth = 1024;
const unsigned int LightComponent::msShadowMapHeight = 1024;
