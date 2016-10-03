#ifndef _ARRAYOBJECT_HPP_
#define _ARRAYOBJECT_HPP_

#include "NonCopyable.hpp"


/**
 * OpenGL vertex array object. It remembers the bindings, so when an object needs to be rendered, you only
 * need to bind its array object.
 */


class ArrayObject : public NonCopyable {

public:

    typedef unsigned int Id;


    void Bind();

    const Id &GetId() const;

    ArrayObject();
    ~ArrayObject();


private:

    Id mId = 0;

};


#endif
