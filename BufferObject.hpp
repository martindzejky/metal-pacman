#ifndef _BUFFEROBJECT_HPP_
#define _BUFFEROBJECT_HPP_

#include "NonCopyable.hpp"


/**
 * OpenGL vertex buffer object wrapper. This resource allows to upload and store
 * the data on the GPU. It is used for rendering.
 */


class BufferObject : public NonCopyable {

public:

    typedef unsigned int Id;
    typedef unsigned int Size;

    enum class Type
    {
        Vertex,
        Color,
        Normal,
        Index
    };


    void Create(Type type);
    void Destroy();

    void Bind(Size elementSize = 3);
    void CopyData(Size size, void* data);

    const Id& GetId() const;
    const Type& GetType() const;


    BufferObject() = default;
    ~BufferObject();


private:

    Id mId = 0;
    Type mType = Type::Vertex;

};


#endif
