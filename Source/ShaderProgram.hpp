#pragma once

#include <string>
#include <glm/glm.hpp>

#include "Singleton.hpp"
#include "Shader.hpp"


/**
 * OpenGL shader program. Links together the vertex and fragment shaders.
 */


class ShaderProgram : public Singleton<ShaderProgram> {

public:

    typedef unsigned int Id;


public:

    static std::shared_ptr<ShaderProgram> Create();

    void Add(Shader::Id id);
    void Link(std::string fragmentOutput);
    void Use();

    void Attribute(std::string name, int size, int stride = 0, int offset = 0);
    void Texture(std::string name = TextureUniformName, int unit = 0);
    void Uniform(std::string name, const glm::mat4 &matrix);

    const Id &GetId() const;

    ShaderProgram();
    ~ShaderProgram();


public:

    static const std::string PositionAttributeName;
    static const std::string ColorAttributeName;
    static const std::string NormalAttributeName;
    static const std::string TexCoordAttributeName;

    static const std::string ModelUniformName;
    static const std::string ViewUniformName;
    static const std::string ProjectionUniformName;
    static const std::string NormalUniformName;
    static const std::string ModelViewUniformName;
    static const std::string ModelViewProjectionUniformName;
    static const std::string TextureUniformName;


private:

    Id mId = 0;

    glm::mat4 mProjection;
    glm::mat4 mView;

};
