#pragma once

#include <string>
#include <unordered_map>

#include <glm/glm.hpp>

#include "Shader.hpp"


/**
 * OpenGL shader program. Links together the vertex and fragment shaders.
 */


class ShaderProgram {

public:

    typedef unsigned int Id;


public:

    static std::shared_ptr<ShaderProgram> Create(std::string name);
    static std::shared_ptr<ShaderProgram> Get(std::string name);

    void Add(Shader::Id id);
    void Link(std::string fragmentOutput = "");
    void Use();

    void Attribute(std::string name, int size, int stride = 0, int offset = 0);
    void Texture(std::string name = TextureUniformName, int unit = 0);
    void Uniform(std::string name, const glm::mat4 &matrix);
    void Uniform(std::string name, const glm::vec3 &vector);
    void Uniform(std::string name, const int &number);
    void Uniform(std::string name, const float &number);

    const Id &GetId() const;

    ShaderProgram(std::string name);
    ~ShaderProgram();


public:

    static const std::string PositionAttributeName;
    static const std::string ColorAttributeName;
    static const std::string NormalAttributeName;
    static const std::string TexCoordAttributeName;
    static const std::string TangentAttributeName;

    static const std::string ModelUniformName;
    static const std::string ViewUniformName;
    static const std::string ProjectionUniformName;
    static const std::string NormalUniformName;
    static const std::string ModelViewUniformName;
    static const std::string ModelViewProjectionUniformName;
    static const std::string TextureUniformName;
    static const std::string NormalMapUniformName;
    static const std::string ReflectionMapUniformName;

    static const std::string LightCountUniformName;
    static const std::string LightPositionsUniformName;
    static const std::string LightColorsUniformName;
    static const std::string LightRadiusesUniformName;


private:

    static std::shared_ptr<ShaderProgram> msCurrent;
    static std::unordered_map<std::string, std::shared_ptr<ShaderProgram>> msShaderPrograms;

    std::string mName;
    Id mId = 0;

    glm::mat4 mProjection;
    glm::mat4 mView;

};
