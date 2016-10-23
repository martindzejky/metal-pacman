#include "LoadState.hpp"

#include "GameState.hpp"
#include "ShaderProgram.hpp"


void LoadState::Start() {
    State::Start();

    // load shaders
    Shader vertexShader("Shaders/Vertex.glsl", Shader::Type::Vertex);
    Shader fragmentShader("Shaders/Fragment.glsl", Shader::Type::Fragment);

    ShaderProgram program;
    program.Add(vertexShader.GetId());
    program.Add(fragmentShader.GetId());
    program.Link("oColor");
    program.Use();


    SwitchInto(std::make_shared<GameState>());
}
