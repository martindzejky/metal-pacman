#include "ShaderProgramTest.hpp"

#include <GL/glew.h>

#include "../Source/Window.hpp"
#include "../Source/Resources.hpp"


void ShaderProgramTest::SetUpTestCase() {
    Window::CreateHidden();
    Resources::Create();
}

void ShaderProgramTest::TearDownTestCase() {
    Window::Destroy();
}

void ShaderProgramTest::SetUp() {
    mShaderProgram = std::make_shared<ShaderProgram>();
}


TEST_F(ShaderProgramTest, Create) {
    EXPECT_NE(mShaderProgram->GetId(), 0) << "Shader program not created";
}


TEST_F(ShaderProgramTest, AddLinkUse) {
    auto vertexShader = Resources::GetSingleton()->Load("VertexShader", "Shaders/Vertex.glsl");
    auto fragmentShader = Resources::GetSingleton()->Load("FragmentShader", "Shaders/Fragment.glsl");

    mShaderProgram->Add(((Shader *) vertexShader.get())->GetId());
    mShaderProgram->Add(((Shader *) fragmentShader.get())->GetId());

    ASSERT_NO_THROW(mShaderProgram->Link("oColor")) << "Shader program can't be linked";

    mShaderProgram->Use();

    GLint active;
    glGetIntegerv(GL_CURRENT_PROGRAM, &active);

    EXPECT_EQ(mShaderProgram->GetId(), active) << "Shader program not used";

    EXPECT_NO_THROW(mShaderProgram->Attribute("iPosition", 3));
    EXPECT_NO_THROW(mShaderProgram->Texture("uTexture"));
    EXPECT_NO_THROW(mShaderProgram->Uniform("uProjection", glm::tmat4x4<double>()));
}
