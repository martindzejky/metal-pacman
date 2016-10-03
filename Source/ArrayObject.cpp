#include "ArrayObject.hpp"

#include <GL/glew.h>


void ArrayObject::Create() {
    glGenVertexArrays(1, &mId);
}

void ArrayObject::Destroy() {
    glDeleteVertexArrays(1, &mId);
    mId = 0;
}

void ArrayObject::Bind() {
    glBindVertexArray(mId);
}

const ArrayObject::Id &ArrayObject::GetId() const {
    return mId;
}

ArrayObject::~ArrayObject() {
    if (mId)
        Destroy();
}
