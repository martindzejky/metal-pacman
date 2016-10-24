#include "GameState.hpp"

#include <GL/glew.h>

#include "Window.hpp"
#include "Input.hpp"
#include "Entity.hpp"
#include "ShaderProgram.hpp"
#include "TransformComponent.hpp"
#include "CameraComponent.hpp"
#include "PlayerComponent.hpp"
#include "Events.hpp"
#include "ArrayObject.hpp"
#include "BufferObject.hpp"


void GameState::Start() {
    State::Start();

    mCamera = Entity::Create();
    mCamera->AttachComponent(std::make_shared<TransformComponent>(0, 0, 200));
    mCamera->AttachComponent(std::make_shared<CameraComponent>(mShaderProgram));
    mCamera->AttachComponent(std::make_shared<PlayerComponent>());

    // CUBE
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

    // transform
    transform = std::make_shared<Transform>(0, 0, -50);

    // M LETTER
    // arrays
    float vertexArray2[] = {
        -60, 60, size + 1,
        -40, 60, size + 1,
        -40, -60, size + 1,
        -60, -60, size + 1,
        60, 60, size + 1,
        40, 60, size + 1,
        40, -60, size + 1,
        60, -60, size + 1,
        -30, 60, size + 1,
        -40, 40, size + 1,
        30, 60, size + 1,
        40, 40, size + 1,
        0, 0, size + 1,
        0, -30, size + 1
    };
    float colorArray2[] = {
        .5f, .6f, 1.f,
        .5f, .6f, 1.f,
        .5f, .6f, 1.f,
        .5f, .6f, 1.f,
        1.f, .8f, .1f,
        1.f, .8f, .1f,
        1.f, .8f, .1f,
        1.f, .8f, .1f,
        .5f, .6f, 1.f,
        .5f, .6f, 1.f,
        1.f, .8f, .1f,
        1.f, .8f, .1f,
        1.f, .3f, .3f,
        1.f, .3f, .3f
    };
    unsigned int indexArray2[] = {
        0, 2, 1,
        0, 3, 2,
        4, 5, 6,
        4, 6, 7,
        1, 12, 8,
        12, 5, 10,
        1, 13, 12,
        12, 13, 5,
        9, 13, 1,
        13, 11, 5
    };

    // array object
    ao2 = std::make_shared<ArrayObject>();
    ao2->Bind();

    // buffer objects
    vertices2 = std::make_shared<BufferObject>(BufferObject::Type::Vertex);
    vertices2->CopyData(sizeof(vertexArray2), (void *) vertexArray2);

    colors2 = std::make_shared<BufferObject>(BufferObject::Type::Vertex);
    colors2->CopyData(sizeof(colorArray2), (void *) colorArray2);

    indices2 = std::make_shared<BufferObject>(BufferObject::Type::Index);
    indices2->CopyData(sizeof(indexArray2), (void *) indexArray2);

    // bind shader attributes
    vertices2->Bind();
    mShaderProgram->Attribute("iPosition", 3);
    colors2->Bind();
    mShaderProgram->Attribute("iColor", 3);

    // transform
    transform2 = std::make_shared<Transform>(0, 0, -50);
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
    events->FireEvent("PostUpdate", nullptr);
    events->FireEvent("Render", nullptr);

    transform->Yaw(.01f, Transform::Space::Global);
    transform2->Yaw(.01f, Transform::Space::Global);
    transform2->Roll(-.02f);

    ao->Bind();
    mShaderProgram->Uniform("uModel", transform->GetMatrix());
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    ao2->Bind();
    mShaderProgram->Uniform("uModel", transform2->GetMatrix());
    glDrawElements(GL_TRIANGLES, 30, GL_UNSIGNED_INT, 0);

    window->SwapBuffers();
    window->PollEvents();

}

GameState::GameState(std::shared_ptr<ShaderProgram> shaderProgram)
    : mShaderProgram(shaderProgram) {
}
