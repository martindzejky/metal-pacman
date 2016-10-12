#include "ArrayObjectTest.hpp"

#include <GL/glew.h>


void ArrayObjectTest::SetUp() {
    mWindow = Window::CreateHidden();
    mArrayObject = std::shared_ptr<ArrayObject>(new ArrayObject());
}


TEST_F(ArrayObjectTest, Create) {
    EXPECT_NE(mArrayObject->GetId(), 0) << "Array object is not created";
}


TEST_F(ArrayObjectTest, Bind) {
    mArrayObject->Bind();

    int bound;
    glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &bound);

    EXPECT_EQ(mArrayObject->GetId(), bound) << "Array object is not bound";
}
