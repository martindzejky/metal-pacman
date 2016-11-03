#include "ShadowMap.hpp"

#include <GL/glew.h>


void ShadowMap::Unbind() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void ShadowMap::Bind() {
    glBindFramebuffer(GL_FRAMEBUFFER, mId);
}

void ShadowMap::BindTexture(int unit) {
    glActiveTexture((GLenum) (GL_TEXTURE0 + unit));
    glBindTexture(GL_TEXTURE_2D, mTextureId);
}

const ShadowMap::Id &ShadowMap::GetId() const {
    return mId;
}

ShadowMap::ShadowMap(Size width, Size height) {
    glGenFramebuffers(1, &mId);
    glGenTextures(1, &mTextureId);

    glBindTexture(GL_TEXTURE_2D, mTextureId);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    GLfloat borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

    Bind();
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, mTextureId, 0);
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
