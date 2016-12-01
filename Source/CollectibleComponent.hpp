#pragma once

#include "Component.hpp"
#include "Transform.hpp"
#include "Events.hpp"


/**
 * A simple component that makes the entity rotate forever. Configurable.
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


