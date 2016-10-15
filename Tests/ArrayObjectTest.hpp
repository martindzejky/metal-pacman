#pragma once

#include <gtest/gtest.h>

#include "../Source/ArrayObject.hpp"


class ArrayObjectTest : public testing::Test {

public:

    static void SetUpTestCase();
    static void TearDownTestCase();
    virtual void SetUp();

    std::shared_ptr<ArrayObject> mArrayObject;

};
