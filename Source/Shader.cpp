#include "Shader.hpp"


#include <fstream>
#include <sstream>

#include <GL/glew.h>

#include "Error.hpp"


void Shader::Load(const std::string &filename, Shader::Type type) {
    if (mId) {
        THROW_ERROR("Shader already loaded");
    }

    std::ifstream file(filename);

    if (!file.is_open()) {
        std::stringstream ess;
        ess << "Can't find shader sourceStream file " << filename;
        THROW_ERROR(ess.str());
    }

    std::stringstream sourceStream;
    sourceStream << file.rdbuf();
    std::string source = sourceStream.str();

    const char* sourcePtr = source.c_str();

    mId = glCreateShader(type == Type::Vertex ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER);
    glShaderSource(mId, 1, &sourcePtr, NULL);
}

void Shader::Destroy() {
    glDeleteShader(mId);
    mId = 0;
}

void Shader::Compile() {
    if (!mId) {
        THROW_ERROR("Shader not loaded");
    }

    glCompileShader(mId);

    GLint status;
    glGetShaderiv(mId, GL_COMPILE_STATUS, &status);

    if (status != GL_TRUE) {
        char buffer[512];
        glGetShaderInfoLog(mId, 512, NULL, buffer);

        std::stringstream ess;
        ess << "Failed to compile shader: " << buffer;
        THROW_ERROR(ess.str());
    }
}

const Shader::Id &Shader::GetId() const {
    return mId;
}

Shader::~Shader() {
    if (mId) {
        Destroy();
    }
}
