#include "BufferObject.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>


void BufferObject::Create(Type type)
{
    mType = type;
    glGenBuffers(1, &mId);
}

void BufferObject::Destroy()
{
    glDeleteBuffers(1, &mId);
    mId = 0;
}

void BufferObject::Bind(Size elementSize)
{
    switch (mType)
    {
        case Type::Vertex:
            glBindBuffer(GL_ARRAY_BUFFER, mId);
            glVertexPointer(elementSize, GL_FLOAT, 0, 0);
            break;

        case Type::Color:
            glBindBuffer(GL_ARRAY_BUFFER, mId);
            glColorPointer(elementSize, GL_FLOAT, 0, 0);
            break;

        case Type::Normal:
            glBindBuffer(GL_ARRAY_BUFFER, mId);
            glNormalPointer(GL_FLOAT, 0, 0);
            break;

        case Type::Index:
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mId);
            glIndexPointer(GL_UNSIGNED_BYTE, 0, 0);
            break;
    }
}

void BufferObject::CopyData(Size size, void* data)
{
    if (mType == Type::Index)
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mId);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    }
    else
    {
        glBindBuffer(GL_ARRAY_BUFFER, mId);
        glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    }
}

const BufferObject::Id& BufferObject::GetId() const
{
    return mId;
}

const BufferObject::Type& BufferObject::GetType() const
{
    return mType;
}

BufferObject::~BufferObject()
{
    if (mId)
        Destroy();
}
