#ifndef _SHADER_HPP_
#define _SHADER_HPP_

#include <string>

#include "NonCopyable.hpp"


/**
 * OpenGL shader. Encapsulates all shader types. Used in shader program.
 */


class Shader : public NonCopyable {

public:

    typedef unsigned int Id;

    enum class Type {
        Vertex,
        Fragment
    };


    void Load(const std::string &filename, Type type);
    void Destroy();

    void Compile();

    const Id &GetId() const;

    Shader() = default;
    ~Shader();


private:

    Id mId = 0;

};


#endif
