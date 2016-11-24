#pragma once

#include "Entity.hpp"


/**
 * This is the global factory for assembling entities. It creates the
 * entities, components, set's up the transform hierarchy, etc.
 */


class EntityFactory {

public:

    static std::shared_ptr<Entity> CreatePlayer(float x = 0, float y = 0, float z = 0);

};


