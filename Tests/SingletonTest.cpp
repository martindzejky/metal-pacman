#include "SingletonTest.hpp"


SINGLETON_DEFINE(SingletonTest);

void SingletonTest::SetSingletonValue(int value) {
    auto ptr = std::shared_ptr<int>(new int());
    *ptr.get() = value;

    SetSingleton(ptr);
}


TEST_F(SingletonTest, SetAndGet) {
    SetSingletonValue(6);
    EXPECT_EQ(*GetSingleton().get(), 6);
}
