#pragma once

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


public:

    const Id &GetId() const;

    Shader(std::string filename, Type type);
    ~Shader();


private:

    Id mId = 0;

};
