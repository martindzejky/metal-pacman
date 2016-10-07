#include "ShaderProgram.hpp"

#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>

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

void ShaderProgram::Uniform(const std::string &name, const glm::mat4 &matrix) {
    auto position = glGetUniformLocation(mId, name.c_str());
    glUniformMatrix4fv(position, 1, GL_FALSE, glm::value_ptr(matrix));
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
