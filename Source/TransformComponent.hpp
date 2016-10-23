#pragma once

#include "Component.hpp"
#include "Transform.hpp"


/**
 * Allows transform to be attached to an entity.
 */


class TransformComponent : public Component, public Transform {

public:

    virtual std::string GetType() const override;

};


