#include "LoadState.hpp"

#include <sstream>

#include "GameState.hpp"
#include "Resources.hpp"
#include "ShaderProgram.hpp"
#include "ShadowMap.hpp"


void LoadState::Start() {
    State::Start();

    auto resources = Resources::GetSingleton();

    // shaders
    auto mainVertexShader = resources->Load("MainVertexShader", "Shaders/MainVertex.glsl");
    auto mainFragmentShader = resources->Load("MainFragmentShader", "Shaders/MainFragment.glsl");
    auto lightVertexShader = resources->Load("LightVertexShader", "Shaders/LightVertex.glsl");
    auto lightGeometryShader = resources->Load("LightGeometryShader", "Shaders/LightGeometry.glsl");
    auto lightFragmentShader = resources->Load("LightFragmentShader", "Shaders/LightFragment.glsl");

    auto mainProgram = ShaderProgram::Create("Main");
    mainProgram->Add(((Shader *) mainVertexShader.get())->GetId());
    mainProgram->Add(((Shader *) mainFragmentShader.get())->GetId());
    mainProgram->Link("oColor");
    mainProgram->Use();

    auto lightProgram = ShaderProgram::Create("Light");
    lightProgram->Add(((Shader *) lightVertexShader.get())->GetId());
    lightProgram->Add(((Shader *) lightGeometryShader.get())->GetId());
    lightProgram->Add(((Shader *) lightFragmentShader.get())->GetId());
    lightProgram->Link();

    // shadow maps
    auto empty = ShadowMap::CreateEmpty();
    for (auto i = 0; i < 12; ++i) {
        std::stringstream shadowMaps;
        shadowMaps << ShaderProgram::ShadowMapsUniformName << "[" << i << "]";
        empty->BindTexture(i + 3);
        ShaderProgram::Get("Main")->Texture(shadowMaps.str(), i + 3);
    }

    // textures
    resources->Load("BlankDiffuseTexture", "Textures/BlankDiffuse.png");
    resources->Load("BlankNormalTexture", "Textures/BlankNormal.png");
    resources->Load("BlankReflectionTexture", "Textures/BlankReflection.png");
    resources->Load("RustDiffuseTexture", "Textures/RustDiffuse.png");
    resources->Load("RustNormalTexture", "Textures/RustNormal.png");
    resources->Load("RustReflectionTexture", "Textures/RustReflection.png");
    resources->Load("RedMetalDiffuseTexture", "Textures/RedMetalDiffuse.png");
    resources->Load("RedMetalNormalTexture", "Textures/RedMetalNormal.png");
    resources->Load("RedMetalReflectionTexture", "Textures/RedMetalReflection.png");
    resources->Load("YellowMetalDiffuseTexture", "Textures/YellowMetalDiffuse.png");
    resources->Load("YellowMetalNormalTexture", "Textures/YellowMetalNormal.png");
    resources->Load("YellowMetalReflectionTexture", "Textures/YellowMetalReflection.png");
    resources->Load("BlueMetalDiffuseTexture", "Textures/BlueMetalDiffuse.png");
    resources->Load("BlueMetalNormalTexture", "Textures/BlueMetalNormal.png");
    resources->Load("BlueMetalReflectionTexture", "Textures/BlueMetalReflection.png");
    resources->Load("GrayMetalDiffuseTexture", "Textures/GrayMetalDiffuse.png");
    resources->Load("GrayMetalNormalTexture", "Textures/GrayMetalNormal.png");
    resources->Load("GrayMetalReflectionTexture", "Textures/GrayMetalReflection.png");
    resources->Load("BlackMetalDiffuseTexture", "Textures/BlackMetalDiffuse.png");
    resources->Load("BlackMetalNormalTexture", "Textures/BlackMetalNormal.png");
    resources->Load("BlackMetalReflectionTexture", "Textures/BlackMetalReflection.png");

    // models
    resources->Load("RoomModel", "Models/Room.ply");
    resources->Load("PacmanBottomModel", "Models/PacmanBottom.ply");
    resources->Load("PacmanTeethBottomModel", "Models/PacmanTeethBottom.ply");
    resources->Load("PacmanTeethTopModel", "Models/PacmanTeethTop.ply");
    resources->Load("PacmanTopModel", "Models/PacmanTop.ply");
    resources->Load("PacmanEyesModel", "Models/PacmanEyes.ply");
    resources->Load("MonsterBodyModel", "Models/MonsterBody.ply");
    resources->Load("MonsterTeethModel", "Models/MonsterTeeth.ply");
    resources->Load("MonsterEyesModel", "Models/MonsterEyes.ply");
    resources->Load("MonsterArmModel", "Models/MonsterArm.ply");
    resources->Load("FloorModel", "Models/Floor.ply");
    resources->Load("Wall1Model", "Models/Wall1.ply");
    resources->Load("Wall2Model", "Models/Wall2.ply");
    resources->Load("Wall3Model", "Models/Wall3.ply");
    resources->Load("SpikesModel", "Models/Spikes.ply");

    SwitchInto(std::make_shared<GameState>());
}
