#include "ShaderProgram.hpp"

#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>

#include "Error.hpp"


std::shared_ptr<ShaderProgram> ShaderProgram::Create(std::string name) {
    auto program = std::make_shared<ShaderProgram>(name);
    msShaderPrograms[name] = program;
    return program;
}

std::shared_ptr<ShaderProgram> ShaderProgram::Get(std::string name) {
    if (msShaderPrograms.count(name)) {
        return msShaderPrograms[name];
    }
    else {
        THROW_ERROR(std::string("Unknown shader program ") + name);
    }
}

void ShaderProgram::Add(Shader::Id id) {
    glAttachShader(mId, id);
}

void ShaderProgram::Link(std::string fragmentOutput) {
    if (fragmentOutput != "") {
        glBindFragDataLocation(mId, 0, fragmentOutput.c_str());
    }
    glLinkProgram(mId);
}

void ShaderProgram::Use() {
    glUseProgram(mId);

    msCurrent = Get(mName);
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

        auto position = glGetUniformLocation(mId, "uModel"); // TODO: Get rid of this
        glUniformMatrix4fv(position, 1, GL_FALSE, glm::value_ptr(matrix));
        position = glGetUniformLocation(mId, ViewUniformName.c_str());
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

void ShaderProgram::Uniform(std::string name, const glm::vec3 &vector) {
    auto position = glGetUniformLocation(mId, name.c_str());
    glUniform3fv(position, 1, glm::value_ptr(vector));
}

void ShaderProgram::Uniform(std::string name, const int &number) {
    auto position = glGetUniformLocation(mId, name.c_str());
    glUniform1i(position, number);
}

void ShaderProgram::Uniform(std::string name, const float &number) {
    auto position = glGetUniformLocation(mId, name.c_str());
    glUniform1f(position, number);
}

const ShaderProgram::Id &ShaderProgram::GetId() const {
    return mId;
}

ShaderProgram::ShaderProgram(std::string name) : mName(name) {
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
const std::string ShaderProgram::TangentAttributeName = "iTangent";

const std::string ShaderProgram::ModelUniformName = "uModel";
const std::string ShaderProgram::ViewUniformName = "uView";
const std::string ShaderProgram::ProjectionUniformName = "uProjection";
const std::string ShaderProgram::NormalUniformName = "uNormal";
const std::string ShaderProgram::ModelViewUniformName = "uModelView";
const std::string ShaderProgram::ModelViewProjectionUniformName = "uModelViewProjection";
const std::string ShaderProgram::TextureUniformName = "uTexture";
const std::string ShaderProgram::NormalMapUniformName = "uNormalMap";
const std::string ShaderProgram::ReflectionMapUniformName = "uReflectionMap";
const std::string ShaderProgram::ShadowMapsUniformName = "uShadowMap";

const std::string ShaderProgram::LightCountUniformName = "uLightCount";
const std::string ShaderProgram::LightPositionsUniformName = "uLightPositions";
const std::string ShaderProgram::LightSpacesUniformName = "uLightSpaces";
const std::string ShaderProgram::LightColorsUniformName = "uLightColors";
const std::string ShaderProgram::LightRadiusesUniformName = "uLightRadiuses";

std::shared_ptr<ShaderProgram> ShaderProgram::msCurrent;
std::unordered_map<std::string, std::shared_ptr<ShaderProgram>> ShaderProgram::msShaderPrograms;
