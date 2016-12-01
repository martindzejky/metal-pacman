#pragma once

#include <random>

#include "Component.hpp"
#include "Events.hpp"


/**
 * Controls the monster movement.
 */


class Entity;

class MonsterAIComponent : public Component {

public:

    virtual void OnAttach(std::weak_ptr<Entity> entity) override;
    virtual void OnDetach() override;
    virtual std::string GetType() const override;

    void Move(float delta);


private:

    std::weak_ptr<Entity> mEntity;
    Events::ListenerId listenerId;

    float mRotationBuffer = 0;

    static std::default_random_engine re;
    static std::uniform_int_distribution<int> dist;

};


