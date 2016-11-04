#include "ShadowMap.hpp"

#include <GL/glew.h>


std::shared_ptr<ShadowMap> ShadowMap::CreateEmpty() {
    auto empty = std::make_shared<ShadowMap>(1, 1);
    msEmpty = empty;
    return empty;
}

void ShadowMap::Unbind() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void ShadowMap::Bind() {
    glBindFramebuffer(GL_FRAMEBUFFER, mId);
}

void ShadowMap::BindTexture(int unit) {
    glActiveTexture((GLenum) (GL_TEXTURE0 + unit));
    glBindTexture(GL_TEXTURE_CUBE_MAP, mTextureId);
}

const ShadowMap::Id &ShadowMap::GetId() const {
    return mId;
}

std::shared_ptr<ShadowMap> ShadowMap::GetEmpty() {
    return msEmpty;
}

ShadowMap::ShadowMap(Size width, Size height) {
    glGenFramebuffers(1, &mId);
    glGenTextures(1, &mTextureId);

    glBindTexture(GL_TEXTURE_CUBE_MAP, mTextureId);
    for (auto i = 0; i < 6; ++i) {
        glTexImage2D((GLenum) (GL_TEXTURE_CUBE_MAP_POSITIVE_X + i), 0, GL_DEPTH_COMPONENT, width, height, 0,
                     GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    Bind();
    glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, mTextureId, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    Unbind();
}

ShadowMap::~ShadowMap() {
    if (mId) {
        glDeleteTextures(1, &mTextureId);
        glDeleteFramebuffers(1, &mId);
    }
}

std::shared_ptr<ShadowMap> ShadowMap::msEmpty;
