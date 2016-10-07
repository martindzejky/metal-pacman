#ifndef _SHADERPROGRAM_HPP_
#define _SHADERPROGRAM_HPP_

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


    void Add(Shader::Id id);
    void Link(const std::string &fragmentOutput);
    void Use();

    void Attribute(const std::string &name, int size, int stride = 0, int offset = 0);
    void Texture(const std::string &name, int unit = 0);
    void Uniform(const std::string &name, const glm::mat4 &matrix);

    const Id &GetId() const;

    ShaderProgram();
    ~ShaderProgram();


private:

    Id mId = 0;

};


#endif
