#include "ShaderProgram.hpp"

#include <GL/glew.h>

#include "Error.hpp"


void ShaderProgram::Add(Shader::Id id) {
    glAttachShader(mId, id);
}

void ShaderProgram::Link(const std::string &fragmentOutput) {
    glBindFragDataLocation(mId, 0, fragmentOutput.c_str());
    glLinkProgram(mId);
}

void ShaderProgram::Use() {
    glUseProgram(mId);
}

void ShaderProgram::Attribute(const std::string &name, int size, int stride, int offset) {
    auto position = (GLuint) glGetAttribLocation(mId, name.c_str());
    glVertexAttribPointer(position, size, GL_FLOAT, GL_FALSE, sizeof(float) * stride,
                          (const void *) (sizeof(float) * offset));
    glEnableVertexAttribArray(position);
}

void ShaderProgram::Texture(const std::string &name, int unit) {
    auto position = glGetUniformLocation(mId, name.c_str());
    glUniform1i(position, unit);
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
