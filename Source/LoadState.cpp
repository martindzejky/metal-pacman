#include "LoadState.hpp"

#include "GameState.hpp"
#include "Resources.hpp"
#include "ShaderProgram.hpp"


void LoadState::Start() {
    State::Start();

    // load shaders
    auto vertexShader = Resources::GetSingleton()->Load("VertexShader", "Shaders/Vertex.glsl");
    auto fragmentShader = Resources::GetSingleton()->Load("FragmentShader", "Shaders/Fragment.glsl");

    auto program = std::make_shared<ShaderProgram>();
    program->Add(((Shader *) vertexShader.get())->GetId());
    program->Add(((Shader *) fragmentShader.get())->GetId());
    program->Link("oColor");
    program->Use();

    SwitchInto(std::make_shared<GameState>(program));
}
