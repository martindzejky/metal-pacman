#include "StateTest.hpp"


void StateTest::SetUp() {
    mState = std::make_shared<StateMock>();
}

void StateMock::Start() {
    State::Start();
    mStartCalled = true;
}

void StateMock::Update(float deltaSeconds) {
    End();
    mUpdateCalled = true;
}

void StateMock::End() {
    State::End();
    mEndCalled = true;
}

void StateMock::Pause() {
    State::Pause();
    mPauseCalled = true;
}

void StateMock::UnPause() {
    State::UnPause();
    mUnPauseCalled = true;
}


TEST_F(StateTest, StartAndStop) {
    EXPECT_NE(State::Current(), mState);

    State::Start(mState);
    auto mock = (StateMock *) mState.get();

    EXPECT_TRUE(mock->mStartCalled);
    EXPECT_TRUE(mock->mUpdateCalled);
    EXPECT_TRUE(mock->mEndCalled);
    EXPECT_FALSE(mock->mPauseCalled);
    EXPECT_FALSE(mock->mUnPauseCalled);
}


TEST_F(StateTest, SwitchAndPause) {
    auto newState = std::make_shared<StateMock>();

    State::SwitchInto(mState);
    EXPECT_TRUE(((StateMock *) mState.get())->mStartCalled);
    EXPECT_EQ(State::Current(), mState);
    EXPECT_FALSE(State::Paused());

    State::SwitchInto(newState);
    EXPECT_TRUE(((StateMock *) mState.get())->mEndCalled);
    EXPECT_TRUE(((StateMock *) newState.get())->mStartCalled);
    EXPECT_EQ(State::Current(), newState);
    EXPECT_FALSE(State::Paused());

    State::PauseWith(mState);
    EXPECT_TRUE(((StateMock *) newState.get())->mPauseCalled);
    EXPECT_EQ(State::Current(), mState);
    EXPECT_EQ(State::Paused(), newState);

    State::SwitchInto(mState);
    EXPECT_TRUE(((StateMock *) newState.get())->mUnPauseCalled);
    EXPECT_TRUE(((StateMock *) newState.get())->mEndCalled);
    EXPECT_EQ(State::Current(), mState);
    EXPECT_FALSE(State::Paused());
}
