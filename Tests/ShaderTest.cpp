#include "ShaderTest.hpp"

#include "../Source/Window.hpp"
#include "../Source/Shader.hpp"
#include "../Source/Resources.hpp"


void ShaderTest::SetUpTestCase() {
    Window::CreateHidden();
    Resources::Create();
}

void ShaderTest::TearDownTestCase() {
    Window::Destroy();
}

TEST_F(ShaderTest, CreateAndCompile) {
    std::shared_ptr<Resource> vertex;
    std::shared_ptr<Resource> fragment;

    EXPECT_NO_THROW(vertex = Resources::GetSingleton()->Load("VertexShader", "Shaders/Vertex.glsl"))
                    << "Vertex shader not compiled";
    EXPECT_NO_THROW(fragment = Resources::GetSingleton()->Load("FragmentShader", "Shaders/Fragment.glsl"))
                    << "Fragment shader not compiled";

    EXPECT_NE(((Shader *) vertex.get())->GetId(), 0) << "Vertex shader not created";
    EXPECT_NE(((Shader *) fragment.get())->GetId(), 0) << "Fragment shader not created";
}
