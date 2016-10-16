#include "BufferObjectTest.hpp"

#include <GL/glew.h>

#include "../Source/Window.hpp"



void BufferObjectTest::SetUpTestCase() {
    Window::CreateHidden();
}

void BufferObjectTest::TearDownTestCase() {
    Window::Destroy();
}

void BufferObjectTest::SetUp() {
    mBufferObjectVertex = std::make_shared<BufferObject>(BufferObject::Type::Vertex);
    mBufferObjectIndex = std::make_shared<BufferObject>(BufferObject::Type::Index);
}


TEST_F(BufferObjectTest, Create) {
    EXPECT_NE(mBufferObjectVertex->GetId(), 0) << "Vertex buffer object is not created";
    EXPECT_NE(mBufferObjectIndex->GetId(), 0) << "Index buffer object is not created";
}


TEST_F(BufferObjectTest, Bind) {
    mBufferObjectVertex->Bind();

    int bound;
    glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &bound);
    EXPECT_EQ(mBufferObjectVertex->GetId(), bound) << "Vertex buffer object is not bound";

    mBufferObjectIndex->Bind();

    glGetIntegerv(GL_ELEMENT_ARRAY_BUFFER_BINDING, &bound);
    EXPECT_EQ(mBufferObjectIndex->GetId(), bound) << "Index buffer object is not bound";
}


TEST_F(BufferObjectTest, Types) {
    EXPECT_EQ(mBufferObjectVertex->GetType(), BufferObject::Type::Vertex) << "Vertex buffer object has wrong type";
    EXPECT_EQ(mBufferObjectIndex->GetType(), BufferObject::Type::Index) << "Index buffer object has wrong type";
}


TEST_F(BufferObjectTest, CopyData) {
    double data[] = { 124.1, 1525.0, 5252.52, -121.11 };
    const int dataLength = 4;

    mBufferObjectVertex->CopyData(sizeof(data), (void *) data);

    int bound;
    glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &bound);
    EXPECT_EQ(mBufferObjectVertex->GetId(), bound) << "Vertex buffer object is not bound";

    double *mapped = (double *) glMapBuffer(GL_ARRAY_BUFFER, GL_READ_ONLY);
    ASSERT_NE(mapped, (double *) NULL) << "Mapped data is null";

    for (auto i = 0; i < dataLength; ++i) {
        EXPECT_EQ(data[i], mapped[i]) << "Mapped data is different at index " << i;
    }
}
