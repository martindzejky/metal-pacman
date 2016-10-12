#include <gtest/gtest.h>
#include <GL/glew.h>

#include "../Source/ArrayObject.hpp"
#include "../Source/Window.hpp"


TEST(ArrayObject, Create) {
    ArrayObject ao;

    EXPECT_GT(ao.GetId(), 0);
}


TEST(ArrayObject, Bind) {
    ArrayObject ao;

    ao.Bind();

    int bound;
    glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &bound);

    EXPECT_EQ(ao.GetId(), bound);
}
