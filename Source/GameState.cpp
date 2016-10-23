#include "GameState.hpp"

#include <GL/glew.h>

#include "Window.hpp"
#include "Input.hpp"
#include "Entity.hpp"
#include "ShaderProgram.hpp"
#include "TransformComponent.hpp"
#include "CameraComponent.hpp"
#include "Events.hpp"
#include "ArrayObject.hpp"
#include "BufferObject.hpp"


void GameState::Start() {
    State::Start();

    mCamera = Entity::Create();
    mCamera->AttachComponent(std::make_shared<TransformComponent>(0, 0, 200));
    mCamera->AttachComponent(std::make_shared<CameraComponent>(mShaderProgram));

    // cube arrays
    float size = 40.f;
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

    // array object
    ao = std::make_shared<ArrayObject>();
    ao->Bind();

    // buffer objects
    vertices = std::make_shared<BufferObject>(BufferObject::Type::Vertex);
    vertices->CopyData(sizeof(vertexArray), (void *) vertexArray);

    colors = std::make_shared<BufferObject>(BufferObject::Type::Vertex);
    colors->CopyData(sizeof(colorArray), (void *) colorArray);

    indices = std::make_shared<BufferObject>(BufferObject::Type::Index);
    indices->CopyData(sizeof(indexArray), (void *) indexArray);

    // bind shader attributes
    vertices->Bind();
    mShaderProgram->Attribute("iPosition", 3);
    colors->Bind();
    mShaderProgram->Attribute("iColor", 3);

}

void GameState::Update(float deltaSeconds) {
    auto window = Window::GetSingleton();
    auto events = Events::GetSingleton();

    if (window->IsClosed()) {
        End();
        return;
    }

    if (Input::IsKeyPressed(Input::Key::Escape)) {
        window->Close();
    }

    window->UpdateViewport();
    window->Clear();

    events->FireEvent("Update", &deltaSeconds);
    events->FireEvent("Render", nullptr);

    indices->Bind();
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    window->SwapBuffers();
    window->PollEvents();

}

GameState::GameState(std::shared_ptr<ShaderProgram> shaderProgram)
    : mShaderProgram(shaderProgram) {
}
