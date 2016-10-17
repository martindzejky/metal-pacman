#pragma once

#include <gtest/gtest.h>

#include "../Source/State.hpp"


class StateTest : public testing::Test {

public:

    virtual void SetUp() override;

    std::shared_ptr<State> mState;

};


class StateMock : public State {

public:

    virtual void Start();
    virtual void Update(float deltaSeconds);
    virtual void End();
    virtual void Pause();
    virtual void UnPause();

    bool mStartCalled = false;
    bool mUpdateCalled = false;
    bool mEndCalled = false;
    bool mPauseCalled = false;
    bool mUnPauseCalled = false;

};
