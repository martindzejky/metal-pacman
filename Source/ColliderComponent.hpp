#pragma once

#include <glm/vec3.hpp>

#include "Component.hpp"
#include "Events.hpp"


/**
 * Physics collider. Can check for collisions with other colliders.
 */


class Entity;

class ColliderComponent : public Component {

public:

    enum class Group {
        Solid = 1 << 1,
        FakeSolid = 1 << 2,
        Player = 1 << 3,
        Enemy = 1 << 4,
        Collectible = 1 << 5,
        Hint = 1 << 6
    };


public:

    virtual void OnAttach(std::weak_ptr<Entity> entity) override;
    virtual std::string GetType() const override;

    bool CheckCollision(int withGroup) const;

    ColliderComponent(float sx, float sy, float sz, Group group);


private:

    std::weak_ptr<Entity> mEntity;
    glm::vec3 mSize;
    Group mGroup;

};


