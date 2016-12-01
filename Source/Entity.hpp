#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <list>

#include "NonCopyable.hpp"


/**
 * Entity represents an object with data and logic. It is composed of components
 * that define this logic.
 */


class Component;


class Entity : public NonCopyable {

public:

    typedef unsigned int Id;


public:

    static std::shared_ptr<Entity> Create();
    static std::shared_ptr<Entity> Get(Id id);
    static const std::unordered_map<Id, std::shared_ptr<Entity>> &GetAll();
    static void Destroy(Id id);
    static void ScheduleDestroy(Id id);
    static void DestroyAll();
    static void ProcessAllScheduled();

    void AttachComponent(std::shared_ptr<Component> component);
    void ScheduleAttachComponent(std::shared_ptr<Component> component);
    std::shared_ptr<Component> GetComponent(std::string type);
    void DetachComponent(std::string type);
    void ScheduleDetachComponent(std::string type);
    void DetachAllComponents();

    void ProcessScheduled();

    const Id &GetId() const;

    ~Entity();


public:

    static const Id Invalid;


private:

    Entity(Id id);


private:

    static Id msLastId;
    static std::unordered_map<Id, std::shared_ptr<Entity>> msEntities;
    static std::list<Id> msScheduled;

    Id mId;
    std::unordered_map<std::string, std::shared_ptr<Component>> mComponents;

    std::list<std::shared_ptr<Component>> mScheduledAttach;
    std::list<std::string> mScheduledDetach;

};


