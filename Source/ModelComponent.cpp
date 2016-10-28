#include "ModelComponent.hpp"

#include "ArrayObject.hpp"
#include "BufferObject.hpp"
#include "ShaderProgram.hpp"
#include "TransformComponent.hpp"
#include "Entity.hpp"
#include "Window.hpp"
#include "Resources.hpp"
#include "ModelData.hpp"


void ModelComponent::OnAttach(std::weak_ptr<Entity> entity) {
    Component::OnAttach(entity);
    mEntity = entity;

    mListenerId = Events::GetSingleton()->AddListener("Render", [this](void *) { OnRender(); });
}

void ModelComponent::OnDetach() {
    Component::OnDetach();
    Events::GetSingleton()->RemoveListener("Render", mListenerId);
}

std::string ModelComponent::GetType() const {
    return "ModelComponent";
}

void ModelComponent::OnRender() {
    auto transform = (TransformComponent *) mEntity.lock()->GetComponent("TransformComponent").get();

    mArrayObject->Bind();
    mShaderProgram->Uniform("uModel", transform->GetMatrix());
    Window::GetSingleton()->DrawElements(mIndexNumber);
}

ModelComponent::ModelComponent(std::string modelName, std::shared_ptr<ShaderProgram> shaderProgram)
    : mShaderProgram(shaderProgram) {
    mArrayObject = std::make_shared<ArrayObject>();
    mVertices = std::make_shared<BufferObject>(BufferObject::Type::Vertex);
    mColors = std::make_shared<BufferObject>(BufferObject::Type::Vertex);
    mIndices = std::make_shared<BufferObject>(BufferObject::Type::Index);

    mArrayObject->Bind();

    auto resource = Resources::GetSingleton()->GetResource(modelName);
    auto model = (ModelData *) resource.get();

    mVertices->CopyData(sizeof(float) * model->GetVertices().size(), (void *) model->GetVertices().data());
    mColors->CopyData(sizeof(float) * model->GetColors().size(), (void *) model->GetColors().data());
    mIndices->CopyData(sizeof(unsigned int) * model->GetIndices().size(), (void *) model->GetIndices().data());
    mIndexNumber = (unsigned int) model->GetIndices().size();

    mVertices->Bind();
    shaderProgram->Attribute("iPosition", 3);
    mColors->Bind();
    shaderProgram->Attribute("iColor", 3);
}
