#pragma once

#include <gtest/gtest.h>

#include "../Source/Singleton.hpp"


class SingletonTest : public testing::Test, public Singleton<int> {

public:

    void SetSingletonValue(int value);

};
