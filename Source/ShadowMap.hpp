#pragma once

#include <memory>
#include "NonCopyable.hpp"


/**
 * OpenGL frame buffer used for shadow maps.
 */


class ShadowMap : public NonCopyable {

public:

    typedef unsigned int Id;
    typedef unsigned int Size;


public:

    static std::shared_ptr<ShadowMap> CreateEmpty();
    static void Unbind();

    void Bind();
    void BindTexture(int unit = 0);

    const Id &GetId() const;

    static std::shared_ptr<ShadowMap> GetEmpty();

    ShadowMap(Size width, Size height);
    ~ShadowMap();


private:

    static std::shared_ptr<ShadowMap> msEmpty;

    Id mId = 0;
    Id mTextureId = 0;

};
