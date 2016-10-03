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


    const Id &GetId() const;

    Shader(const std::string &filename, Type type);
    ~Shader();


private:

    Id mId = 0;

};


#endif
