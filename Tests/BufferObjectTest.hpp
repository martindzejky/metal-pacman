#pragma once

#include <gtest/gtest.h>

#include "../Source/BufferObject.hpp"
#include "../Source/Window.hpp"


class BufferObjectTest : public testing::Test {

public:

    virtual void SetUp();

    std::shared_ptr<Window> mWindow;
    std::shared_ptr<BufferObject> mBufferObjectVertex;
    std::shared_ptr<BufferObject> mBufferObjectIndex;

};
