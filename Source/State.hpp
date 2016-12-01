#pragma once

#include <memory>

#include "NonCopyable.hpp"


/**
 * This class encapsulates a state of the game. Each state controls the game loop
 * and contains entities.
 */


class State : public NonCopyable {

public:

    static void Start(std::shared_ptr<State> state);
    static void SwitchInto(std::shared_ptr<State> newState);
    static void PauseWith(std::shared_ptr<State> newState);

    virtual void Start();
    virtual void Update(float deltaSeconds) = 0;
    virtual void End();
    virtual void Pause();
    virtual void UnPause();

    const bool &IsRunning() const;
    const bool &IsPaused() const;

    static std::shared_ptr<State> Current();
    static std::shared_ptr<State> Paused();

    virtual ~State() = default;


private:

    static void Run();

private:

    static std::shared_ptr<State> msCurrent;
    static std::shared_ptr<State> msPaused;
    static float mFPSSum;
    static unsigned int mFPSCount;

    bool mRunning;
    bool mPaused;

};


