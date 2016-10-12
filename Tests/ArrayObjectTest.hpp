#pragma once

#include <gtest/gtest.h>

#include "../Source/ArrayObject.hpp"
#include "../Source/Window.hpp"


class ArrayObjectTest : public testing::Test {

public:

    virtual void SetUp();

    std::shared_ptr<Window> mWindow;
    std::shared_ptr<ArrayObject> mArrayObject;

};
