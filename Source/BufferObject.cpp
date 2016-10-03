#include "BufferObject.hpp"

#include <GL/glew.h>

#include "Error.hpp"


void BufferObject::Bind(Size elementSize) {
    if (mType == Type::Index) {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mId);
    } else {
        glBindBuffer(GL_ARRAY_BUFFER, mId);
    }
}

void BufferObject::CopyData(Size size, void *data) {
    if (mType == Type::Index) {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mId);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    } else {
        glBindBuffer(GL_ARRAY_BUFFER, mId);
        glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    }
}

const BufferObject::Id &BufferObject::GetId() const {
    return mId;
}

const BufferObject::Type &BufferObject::GetType() const {
    return mType;
}

BufferObject::BufferObject(Type type) {
    mType = type;
    glGenBuffers(1, &mId);
}

BufferObject::~BufferObject() {
    if (mId) {
        glDeleteBuffers(1, &mId);
    }
}
