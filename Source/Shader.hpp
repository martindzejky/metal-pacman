#pragma once

#include <string>

#include "Resource.hpp"


/**
 * OpenGL shader. Encapsulates all shader types. Used in shader program.
 */


class Shader : public Resource {

public:

    typedef unsigned int Id;

    enum class Type {
        Vertex,
        Geometry,
        Fragment
    };


public:

    virtual void Load(std::string path) override;

    const Id &GetId() const;

    Shader(std::string name, Shader::Type type);
    ~Shader();


private:

    Id mId = 0;
    Type mType;

};
