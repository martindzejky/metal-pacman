#include "GameState.hpp"

#include "Window.hpp"
#include "Input.hpp"
#include "Entity.hpp"
#include "ShaderProgram.hpp"
#include "TransformComponent.hpp"
#include "CameraComponent.hpp"
#include "PlayerComponent.hpp"
#include "ColorCubeComponent.hpp"
#include "ArrayObject.hpp"
#include "BufferObject.hpp"


void GameState::Start() {
    State::Start();

    mCamera = Entity::Create();
    mCamera->AttachComponent(std::make_shared<TransformComponent>(0, 0, 200));
    mCamera->AttachComponent(std::make_shared<CameraComponent>(mShaderProgram));
    mCamera->AttachComponent(std::make_shared<PlayerComponent>());

    mCube = Entity::Create();
    mCube->AttachComponent(std::make_shared<TransformComponent>());
    mCube->AttachComponent(std::make_shared<ColorCubeComponent>(40, mShaderProgram));

    // M LETTER
    float size = 40.f;

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
    transform2 = std::make_shared<Transform>();
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

    transform2->Yaw(.01f, Transform::Space::Global);
    transform2->Roll(-.02f);

    ao2->Bind();
    mShaderProgram->Uniform("uModel", transform2->GetMatrix());
    window->DrawElements(30);

    window->SwapBuffers();
    window->PollEvents();

}

GameState::GameState(std::shared_ptr<ShaderProgram> shaderProgram)
    : mShaderProgram(shaderProgram) {
}
