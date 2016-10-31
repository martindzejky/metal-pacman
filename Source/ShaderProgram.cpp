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
    if (name.find("Projection") != std::string::npos) {
        mProjection = matrix;
    }
    else if (name.find("View") != std::string::npos) {
        mView = matrix;
    }
    else if (name.find("Model") != std::string::npos) {
        auto modelView = mView * matrix;
        auto modelViewProjection = mProjection * modelView;
        auto normal = glm::transpose(glm::inverse(glm::mat3(modelView)));

        auto position = glGetUniformLocation(mId, "uModelView");
        glUniformMatrix4fv(position, 1, GL_FALSE, glm::value_ptr(modelView));
        position = glGetUniformLocation(mId, "uModelViewProjection");
        glUniformMatrix4fv(position, 1, GL_FALSE, glm::value_ptr(modelViewProjection));
        position = glGetUniformLocation(mId, "uNormal");
        glUniformMatrix4fv(position, 1, GL_FALSE, glm::value_ptr(normal));
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
