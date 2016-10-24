#include "Shader.hpp"


#include <fstream>
#include <sstream>

#include <GL/glew.h>

#include "Error.hpp"


void Shader::Load(std::string path) {
    std::ifstream file(path);

    if (!file.is_open()) {
        std::stringstream ess;
        ess << "Can't find shader source file " << path;
        THROW_ERROR(ess.str());
    }

    std::stringstream sourceStream;
    sourceStream << file.rdbuf();
    std::string source = sourceStream.str();

    const char *sourcePtr = source.c_str();

    mId = glCreateShader(mType == Type::Vertex ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER);
    glShaderSource(mId, 1, &sourcePtr, nullptr);
    glCompileShader(mId);

    GLint status;
    glGetShaderiv(mId, GL_COMPILE_STATUS, &status);

    if (status != GL_TRUE) {
        char buffer[512];
        glGetShaderInfoLog(mId, 512, nullptr, buffer);

        std::stringstream ess;
        ess << "Failed to compile shader: " << buffer;
        THROW_ERROR(ess.str());
    }
}

const Shader::Id &Shader::GetId() const {
    return mId;
}

Shader::Shader(std::string name, Shader::Type type)
    : Resource(name), mType(type) {}

Shader::~Shader() {
    if (mId) {
        glDeleteShader(mId);
    }
}
