#pragma once

#include "Component.hpp"
#include "Transform.hpp"
#include "Events.hpp"


/**
 * Represents an object that can be collected. Once all are collected, moves to the success state.
 */


class CollectibleComponent : public Component {

public:

    virtual void OnAttach(std::weak_ptr<Entity> entity) override;
    virtual std::string GetType() const override;

    CollectibleComponent();
    ~CollectibleComponent();


private:

    std::weak_ptr<Entity> mEntity;

    static unsigned int mCount;

};


