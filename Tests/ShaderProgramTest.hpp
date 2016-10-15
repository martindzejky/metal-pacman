#pragma once

#include <gtest/gtest.h>

#include "../Source/ShaderProgram.hpp"


class ShaderProgramTest : public testing::Test {

public:

    static void SetUpTestCase();
    static void TearDownTestCase();
    virtual void SetUp() override;

    std::shared_ptr<ShaderProgram> mShaderProgram;

};
