#pragma once

#include "NonCopyable.hpp"


/**
 * OpenGL frame buffer. Usable as a render target, for example for shadow maps.
 * Note: Currently supports only shadow maps!
 */


class FrameBuffer : public NonCopyable {

public:

    typedef unsigned int Id;
    typedef unsigned int Size;


public:

    static void Unbind();

    void Bind();
    void BindTexture(int unit = 0);

    const Id &GetId() const;


    FrameBuffer(Size width, Size height);
    ~FrameBuffer();


private:

    Id mId = 0;
    Id mTextureId = 0;

};
