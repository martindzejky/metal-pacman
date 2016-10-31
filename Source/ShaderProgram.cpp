#include "ShaderProgram.hpp"

#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>


std::shared_ptr<ShaderProgram> ShaderProgram::Create() {
    auto program = std::make_shared<ShaderProgram>();
    SetSingleton(program);
    return program;
}

void ShaderProgram::Add(Shader::Id id) {
    glAttachShader(mId, id);
}

void ShaderProgram::Link(std::string fragmentOutput) {
    glBindFragDataLocation(mId, 0, fragmentOutput.c_str());
    glLinkProgram(mId);
}

void ShaderProgram::Use() {
    glUseProgram(mId);
}

void ShaderProgram::Attribute(std::string name, int size, int stride, int offset) {
    auto position = (GLuint) glGetAttribLocation(mId, name.c_str());
    glVertexAttribPointer(position, size, GL_FLOAT, GL_FALSE, sizeof(float) * stride,
                          (const void *) (sizeof(float) * offset));
    glEnableVertexAttribArray(position);
}

void ShaderProgram::Texture(std::string name, int unit) {
    auto position = glGetUniformLocation(mId, name.c_str());
    glUniform1i(position, unit);
}

void ShaderProgram::Uniform(std::string name, const glm::mat4 &matrix) {
    if (name == ProjectionUniformName) {
        mProjection = matrix;
    }
    else if (name == ViewUniformName) {
        mView = matrix;
    }
    else if (name == ModelUniformName) {
        auto modelView = mView * matrix;
        auto modelViewProjection = mProjection * modelView;
        auto normal = glm::transpose(glm::inverse(glm::mat3(modelView)));

        auto position = glGetUniformLocation(mId, ViewUniformName.c_str());
        glUniformMatrix4fv(position, 1, GL_FALSE, glm::value_ptr(mView));
        position = glGetUniformLocation(mId, ModelViewUniformName.c_str());
        glUniformMatrix4fv(position, 1, GL_FALSE, glm::value_ptr(modelView));
        position = glGetUniformLocation(mId, ModelViewProjectionUniformName.c_str());
        glUniformMatrix4fv(position, 1, GL_FALSE, glm::value_ptr(modelViewProjection));
        position = glGetUniformLocation(mId, NormalUniformName.c_str());
        glUniformMatrix3fv(position, 1, GL_FALSE, glm::value_ptr(normal));
    }
    else {
        auto position = glGetUniformLocation(mId, name.c_str());
        glUniformMatrix4fv(position, 1, GL_FALSE, glm::value_ptr(matrix));
    }
}

const ShaderProgram::Id &ShaderProgram::GetId() const {
    return mId;
}

ShaderProgram::ShaderProgram() {
    mId = glCreateProgram();
}

ShaderProgram::~ShaderProgram() {
    if (mId) {
        glDeleteProgram(mId);
    }
}

const std::string ShaderProgram::PositionAttributeName = "iPosition";
const std::string ShaderProgram::ColorAttributeName = "iColor";
const std::string ShaderProgram::NormalAttributeName = "iNormal";
const std::string ShaderProgram::TexCoordAttributeName = "iTexCoord";

const std::string ShaderProgram::ModelUniformName = "uModel";
const std::string ShaderProgram::ViewUniformName = "uView";
const std::string ShaderProgram::ProjectionUniformName = "uProjection";
const std::string ShaderProgram::NormalUniformName = "uNormal";
const std::string ShaderProgram::ModelViewUniformName = "uModelView";
const std::string ShaderProgram::ModelViewProjectionUniformName = "uModelViewProjection";
const std::string ShaderProgram::TextureUniformName = "uTexture";
