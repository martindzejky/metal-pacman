#pragma once

#include <gtest/gtest.h>

#include "../Source/BufferObject.hpp"


class BufferObjectTest : public testing::Test {

public:

    static void SetUpTestCase();
    static void TearDownTestCase();
    virtual void SetUp() override;

    std::shared_ptr<BufferObject> mBufferObjectVertex;
    std::shared_ptr<BufferObject> mBufferObjectIndex;

};
