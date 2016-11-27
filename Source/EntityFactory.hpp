#pragma once

#include "Entity.hpp"


/**
 * This is the global factory for assembling entities. It creates the
 * entities, components, set's up the transform hierarchy, etc.
 */


class EntityFactory {

public:

    static std::shared_ptr<Entity> CreatePlayer(float x = 0, float y = 0, float z = 0);
    static std::shared_ptr<Entity> CreateMonster(float x = 0, float y = 0, float z = 0);
    static std::shared_ptr<Entity> CreateFloor(float x = 0, float y = 0, float z = 0);
    static std::shared_ptr<Entity> CreateWall(int variant, float x = 0, float y = 0, float z = 0);

};


