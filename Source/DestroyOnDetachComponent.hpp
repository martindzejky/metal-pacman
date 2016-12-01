#pragma once

#include "Component.hpp"
#include "Events.hpp"
#include "Entity.hpp"


/**
 * Destroys an entity when detached.
 */


class DestroyOnDetachComponent : public Component {

public:

    void OnDetach() override;
    virtual std::string GetType() const override;

    DestroyOnDetachComponent(Entity::Id id);


private:

    Entity::Id mId;

};


