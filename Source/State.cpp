#include "State.hpp"


void State::Start(std::shared_ptr<State> state) {
    SwitchInto(state);
    Run();
}

void State::SwitchInto(std::shared_ptr<State> newState) {
    if (msCurrent && msCurrent->IsRunning()) {
        msCurrent->End();
    }

    if (msPaused && msPaused->IsPaused()) {
        msPaused->UnPause();
        msPaused->End();
    }

    msPaused = std::shared_ptr<State>();
    msCurrent = newState;
    msCurrent->Start();
}

void State::PauseWith(std::shared_ptr<State> newState) {
    msPaused = msCurrent;
    msCurrent = newState;

    msPaused->Pause();
    msCurrent->Start();
}

void State::Start() {
    mRunning = true;
}

void State::End() {
    mRunning = false;
}

void State::Pause() {
    mPaused = true;
}

void State::UnPause() {
    mPaused = false;
}

const bool &State::IsRunning() const {
    return mRunning;
}

const bool &State::IsPaused() const {
    return mPaused;
}

std::shared_ptr<State> State::Current() {
    return msCurrent;
}

std::shared_ptr<State> State::Paused() {
    return msPaused;
}

void State::Run() {
    while (true) {
        if (msCurrent && msCurrent->IsRunning()) {
            msCurrent->Update(0);
        }
        else {
            if (msCurrent) {
                msCurrent->End();
                msCurrent = std::shared_ptr<State>(); // TODO: Try nullptr
            }

            if (msPaused && msPaused->IsPaused()) {
                msCurrent = msPaused;
                msPaused = std::shared_ptr<State>();

                msCurrent->UnPause();
            }
            else {
                break;
            }
        }
    }
}

std::shared_ptr<State> State::msCurrent;
std::shared_ptr<State> State::msPaused;
