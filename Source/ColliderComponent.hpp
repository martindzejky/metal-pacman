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
        Solid,
        FakeSolid,
        Player,
        Enemy,
        Collectible
    };


public:

    virtual void OnAttach(std::weak_ptr<Entity> entity) override;
    virtual std::string GetType() const override;

    bool CheckCollision(Group withGroup) const;

    ColliderComponent(float sx, float sy, float sz, Group group);


private:

    std::weak_ptr<Entity> mEntity;
    glm::vec3 mSize;
    Group mGroup;

};


