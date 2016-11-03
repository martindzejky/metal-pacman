#pragma once

#include "NonCopyable.hpp"


/**
 * OpenGL frame buffer used for shadow maps.
 */


class ShadowMap : public NonCopyable {

public:

    typedef unsigned int Id;
    typedef unsigned int Size;


public:

    static void Unbind();

    void Bind();
    void BindTexture(int unit = 0);

    const Id &GetId() const;


    ShadowMap(Size width, Size height);
    ~ShadowMap();


private:

    Id mId = 0;
    Id mTextureId = 0;

};
