#pragma once

#include <string>
#include <glm/glm.hpp>

#include "NonCopyable.hpp"
#include "Shader.hpp"


/**
 * OpenGL shader program. Links together the vertex and fragment shaders.
 */


class ShaderProgram : public NonCopyable {

public:

    typedef unsigned int Id;


public:

    void Add(Shader::Id id);
    void Link(std::string fragmentOutput);
    void Use();

    void Attribute(std::string name, int size, int stride = 0, int offset = 0);
    void Texture(std::string name, int unit = 0);
    void Uniform(std::string name, const glm::mat4 &matrix);

    const Id &GetId() const;

    ShaderProgram();
    ~ShaderProgram();


private:

    Id mId = 0;

};
