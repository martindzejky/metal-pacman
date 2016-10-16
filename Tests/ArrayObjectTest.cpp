#include "ArrayObjectTest.hpp"

#include <GL/glew.h>

#include "../Source/Window.hpp"


void ArrayObjectTest::SetUpTestCase() {
    Window::CreateHidden();
}

void ArrayObjectTest::TearDownTestCase() {
    Window::Destroy();
}

void ArrayObjectTest::SetUp() {
    mArrayObject = std::make_shared<ArrayObject>();
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
