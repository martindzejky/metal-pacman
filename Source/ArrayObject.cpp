#include "ArrayObject.hpp"

#include <GL/glew.h>


void ArrayObject::Bind() {
    glBindVertexArray(mId);
}

const ArrayObject::Id &ArrayObject::GetId() const {
    return mId;
}

ArrayObject::ArrayObject() {
    glGenVertexArrays(1, &mId);
}

ArrayObject::~ArrayObject() {
    if (mId) {
        glDeleteVertexArrays(1, &mId);
    }
}
