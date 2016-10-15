#include "ShaderTest.hpp"

#include "../Source/Window.hpp"


void ShaderTest::SetUpTestCase() {
    Window::CreateHidden();
}

void ShaderTest::TearDownTestCase() {
    Window::Destroy();
}

TEST_F(ShaderTest, CreateAndCompile) {
    std::shared_ptr<Shader> vertex;
    std::shared_ptr<Shader> fragment;

    EXPECT_NO_THROW(vertex = std::shared_ptr<Shader>(new Shader("Shaders/Vertex.glsl", Shader::Type::Vertex)))
        << "Vertex shader not compiled";
    EXPECT_NO_THROW(fragment = std::shared_ptr<Shader>(new Shader("Shaders/Fragment.glsl", Shader::Type::Fragment)))
        << "Fragment shader not compiled";

    EXPECT_NE(vertex->GetId(), 0) << "Vertex shader not created";
    EXPECT_NE(fragment->GetId(), 0) << "Fragment shader not created";
}
