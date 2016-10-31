#include "ModelComponent.hpp"

#include "ArrayObject.hpp"
#include "BufferObject.hpp"
#include "ShaderProgram.hpp"
#include "TransformComponent.hpp"
#include "Entity.hpp"
#include "Window.hpp"
#include "Resources.hpp"
#include "ModelData.hpp"
#include "Texture.hpp"


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

    ((Texture*) mTexture.get())->Bind();
    ShaderProgram::GetSingleton()->Texture();

    mArrayObject->Bind();
    ShaderProgram::GetSingleton()->Uniform(ShaderProgram::ModelUniformName, transform->GetMatrix());
    Window::GetSingleton()->DrawElements(mIndexNumber);
}

ModelComponent::ModelComponent(std::string modelName, std::string textureName) {
    mArrayObject = std::make_shared<ArrayObject>();
    mArrayObject->Bind();

    auto resource = Resources::GetSingleton()->GetResource(modelName);
    auto model = (ModelData *) resource.get();

    mVertices = std::make_shared<BufferObject>(BufferObject::Type::Vertex);
    mVertices->CopyData(sizeof(float) * model->GetVertices().size(), (void *) model->GetVertices().data());

    if (model->GetColors().size() > 0) {
        mColors = std::make_shared<BufferObject>(BufferObject::Type::Vertex);
        mColors->CopyData(sizeof(float) * model->GetColors().size(), (void *) model->GetColors().data());
    }

    mNormals = std::make_shared<BufferObject>(BufferObject::Type::Vertex);
    mNormals->CopyData(sizeof(float) * model->GetNormals().size(), (void *) model->GetNormals().data());

    if (model->GetTexCoords().size() > 0) {
        mTexCoords = std::make_shared<BufferObject>(BufferObject::Type::Vertex);
        mTexCoords->CopyData(sizeof(float) * model->GetTexCoords().size(), (void *) model->GetTexCoords().data());
    }

    mIndices = std::make_shared<BufferObject>(BufferObject::Type::Index);
    mIndices->CopyData(sizeof(unsigned int) * model->GetIndices().size(), (void *) model->GetIndices().data());
    mIndexNumber = (unsigned int) model->GetIndices().size();

    mVertices->Bind();
    ShaderProgram::GetSingleton()->Attribute(ShaderProgram::PositionAttributeName, 3);

    if (mColors) {
        mColors->Bind();
        ShaderProgram::GetSingleton()->Attribute(ShaderProgram::ColorAttributeName, 3);
    }

    mNormals->Bind();
    ShaderProgram::GetSingleton()->Attribute(ShaderProgram::NormalAttributeName, 3);

    if (mTexCoords) {
        mTexCoords->Bind();
        ShaderProgram::GetSingleton()->Attribute(ShaderProgram::TexCoordAttributeName, 2);
    }

    mTexture = Resources::GetSingleton()->GetResource(textureName);
}
