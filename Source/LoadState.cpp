#include "LoadState.hpp"

#include "GameState.hpp"
#include "Resources.hpp"
#include "ShaderProgram.hpp"


void LoadState::Start() {
    State::Start();

    auto resources = Resources::GetSingleton();

    // shaders
    auto vertexShader = resources->Load("VertexShader", "Shaders/Vertex.glsl");
    auto fragmentShader = resources->Load("FragmentShader", "Shaders/Fragment.glsl");

    auto program = ShaderProgram::Create();
    program->Add(((Shader *) vertexShader.get())->GetId());
    program->Add(((Shader *) fragmentShader.get())->GetId());
    program->Link("oColor");
    program->Use();

    // textures
    resources->Load("BlankDiffuseTexture", "Textures/BlankDiffuse.png");
    resources->Load("BlankNormalTexture", "Textures/BlankNormal.png");
    resources->Load("BlankReflectionTexture", "Textures/BlankReflection.png");
    resources->Load("CobbleDiffuseTexture", "Textures/CobblestoneDiffuse.png");
    resources->Load("CobbleNormalTexture", "Textures/CobblestoneNormal.png");
    resources->Load("CobbleReflectionTexture", "Textures/CobblestoneReflection.png");

    // models
    resources->Load("RoomModel", "Models/Room.ply");

    SwitchInto(std::make_shared<GameState>());
}
