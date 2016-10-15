#include <gtest/gtest.h>

#include "../Source/Error.hpp"


TEST(Error, Throw) {
    EXPECT_THROW(THROW_ERROR(""), Error) << "Error not thrown";
}
