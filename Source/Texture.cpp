#include "Texture.hpp"

#include <vector>
#include <string>

#include <GL/glew.h>
#include <lodepng.h>

#include "Error.hpp"


void Texture::Load(std::string path) {
    std::vector<unsigned char> pixels;
    unsigned int width, height;

    auto error = lodepng::decode(pixels, width, height, path);

    if (error) {
        THROW_ERROR(std::string("Failed to load texture ") + path + ": " + lodepng_error_text(error));
    }

    Bind();

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels.data());
}

void Texture::Bind(int unit) {
    switch (unit) {
        default:
            glActiveTexture(GL_TEXTURE0);
            break;

        case 1:
            glActiveTexture(GL_TEXTURE1);
            break;

        case 2:
            glActiveTexture(GL_TEXTURE2);
            break;

        case 3:
            glActiveTexture(GL_TEXTURE3);
            break;
    }
    glBindTexture(GL_TEXTURE_2D, mId);
}

const Texture::Id &Texture::GetId() const {
    return mId;
}

Texture::Texture(std::string name) : Resource(name) {
    glGenTextures(1, &mId);
}

Texture::~Texture() {
    if (mId) {
        glDeleteTextures(1, &mId);
    }
}
