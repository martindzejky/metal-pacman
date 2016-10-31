#pragma once

#include "Resource.hpp"


/**
 * An OpenGL texture loaded from a PNG file.
 */


class Texture : public Resource {

public:

    typedef unsigned int Id;


public:

    virtual void Load(std::string path) override;
    void Bind();

    const Id &GetId() const;

    Texture(std::string name);
    ~Texture();


private:

    Id mId = 0;

};


