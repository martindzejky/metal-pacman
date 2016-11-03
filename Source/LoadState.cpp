#include "LoadState.hpp"

#include "GameState.hpp"
#include "Resources.hpp"
#include "ShaderProgram.hpp"


void LoadState::Start() {
    State::Start();

    auto resources = Resources::GetSingleton();

    // shaders
    auto mainVertexShader = resources->Load("MainVertexShader", "Shaders/MainVertex.glsl");
    auto mainFragmentShader = resources->Load("MainFragmentShader", "Shaders/MainFragment.glsl");
    auto lightVertexShader = resources->Load("LightVertexShader", "Shaders/LightVertex.glsl");
    auto lightFragmentShader = resources->Load("LightFragmentShader", "Shaders/LightFragment.glsl");

    auto mainProgram = ShaderProgram::Create("Main");
    mainProgram->Add(((Shader *) mainVertexShader.get())->GetId());
    mainProgram->Add(((Shader *) mainFragmentShader.get())->GetId());
    mainProgram->Link("oColor");
    mainProgram->Use();

    auto lightProgram = ShaderProgram::Create("Light");
    lightProgram->Add(((Shader *) lightVertexShader.get())->GetId());
    lightProgram->Add(((Shader *) lightFragmentShader.get())->GetId());
    lightProgram->Link();

    // textures
    resources->Load("BlankDiffuseTexture", "Textures/BlankDiffuse.png");
    resources->Load("BlankNormalTexture", "Textures/BlankNormal.png");
    resources->Load("BlankReflectionTexture", "Textures/BlankReflection.png");
    resources->Load("CobbleDiffuseTexture", "Textures/CobblestoneDiffuse.png");
    resources->Load("CobbleNormalTexture", "Textures/CobblestoneNormal.png");
    resources->Load("CobbleReflectionTexture", "Textures/CobblestoneReflection.png");
    resources->Load("WoodDiffuseTexture", "Textures/WoodDiffuse.png");
    resources->Load("WoodNormalTexture", "Textures/WoodNormal.png");
    resources->Load("WoodReflectionTexture", "Textures/WoodReflection.png");

    // models
    resources->Load("RoomModel", "Models/Room.ply");
    resources->Load("TableModel", "Models/Table.ply");

    SwitchInto(std::make_shared<GameState>());
}
