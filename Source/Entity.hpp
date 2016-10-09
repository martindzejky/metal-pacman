#pragma once

#include <memory>
#include <string>
#include <unordered_map>


/**
 * Entity represents an object with data and logic. It is composed of components
 * that define this logic.
 */


class Component;


class Entity {

public:

    typedef unsigned int Id;


public:

    static std::shared_ptr<Entity> Create();
    static std::shared_ptr<Entity> Get(Id id);
    static void Destroy(Entity::Id id);

    void AttachComponent(std::shared_ptr<Component> component);
    std::shared_ptr<Component> GetComponent(std::string type);
    void DetachComponent(std::string type);
    void DetachAllComponents();

    const Id &GetId() const;

    Entity(Id id);
    ~Entity();


public:

    static const Id Invalid;


private:

    static Id msLastId;
    static std::unordered_map<Id, std::shared_ptr<Entity>> msEntities;

    Id mId;
    std::unordered_map<std::string, std::shared_ptr<Component>> mComponents;

};


