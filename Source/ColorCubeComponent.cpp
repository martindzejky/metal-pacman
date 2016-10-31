#include "ColorCubeComponent.hpp"

#include "ArrayObject.hpp"
#include "BufferObject.hpp"
#include "ShaderProgram.hpp"
#include "TransformComponent.hpp"
#include "Entity.hpp"
#include "Window.hpp"
#include "Resources.hpp"
#include "Texture.hpp"


void ColorCubeComponent::OnAttach(std::weak_ptr<Entity> entity) {
    Component::OnAttach(entity);
    mEntity = entity;

    listenerId = Events::GetSingleton()->AddListener("Render", [this](void *) { OnRender(); });
}

void ColorCubeComponent::OnDetach() {
    Component::OnDetach();
    Events::GetSingleton()->RemoveListener("Render", listenerId);
}

std::string ColorCubeComponent::GetType() const {
    return "ColorCubeComponent";
}

void ColorCubeComponent::OnRender() {
    auto transform = (TransformComponent *) mEntity.lock()->GetComponent("TransformComponent").get();
    auto blank = Resources::GetSingleton()->GetResource("BlankTexture");

    ((Texture*) blank.get())->Bind();
    ShaderProgram::GetSingleton()->Texture("uTexture");

    mArrayObject->Bind();
    ShaderProgram::GetSingleton()->Uniform("uModel", transform->GetMatrix());
    Window::GetSingleton()->DrawElements(36);
}

ColorCubeComponent::ColorCubeComponent(float size) {
    mArrayObject = std::make_shared<ArrayObject>();
    mVertices = std::make_shared<BufferObject>(BufferObject::Type::Vertex);
    mColors = std::make_shared<BufferObject>(BufferObject::Type::Vertex);
    mIndices = std::make_shared<BufferObject>(BufferObject::Type::Index);

    mArrayObject->Bind();

    CopyVertices(size);
    CopyColors();
    CopyIndices();

    mVertices->Bind();
    ShaderProgram::GetSingleton()->Attribute("iPosition", 3);
    mColors->Bind();
    ShaderProgram::GetSingleton()->Attribute("iColor", 3);
}

void ColorCubeComponent::CopyVertices(float size) {
    float vertexArray[] = {
        -size, -size, -size,
        -size, -size, size,
        -size, size, size,
        -size, size, -size,
        size, -size, -size,
        size, -size, size,
        size, size, size,
        size, size, -size
    };
    mVertices->CopyData(sizeof(vertexArray), (void *) vertexArray);
}

void ColorCubeComponent::CopyColors() {
    float colorArray[] = {
        0.f, 0.f, 0.f,
        1.f, 0.f, 0.f,
        1.f, 1.f, 0.f,
        0.f, 1.f, 0.f,
        0.f, 0.f, 1.f,
        1.f, 0.f, 1.f,
        1.f, 1.f, 1.f,
        0.f, 1.f, 1.f
    };
    mColors->CopyData(sizeof(colorArray), (void *) colorArray);
}

void ColorCubeComponent::CopyIndices() {
    unsigned int indexArray[] = {
        0, 1, 2,
        0, 2, 3,
        4, 6, 5,
        4, 7, 6,
        1, 5, 6,
        1, 6, 2,
        0, 3, 7,
        0, 7, 4,
        0, 4, 5,
        0, 5, 1,
        2, 6, 7,
        2, 7, 3
    };
    mIndices->CopyData(sizeof(indexArray), (void *) indexArray);
}
