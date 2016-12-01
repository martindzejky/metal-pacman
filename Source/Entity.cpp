#include "Entity.hpp"

#include <memory>

#include "Component.hpp"
#include "Error.hpp"


std::shared_ptr<Entity> Entity::Create() {
    Id entityId = ++msLastId;
    std::shared_ptr<Entity> entity(new Entity(entityId));

    msEntities[entityId] = entity;
    return entity;
}

std::shared_ptr<Entity> Entity::Get(Entity::Id id) {
    if (msEntities.count(id)) {
        return msEntities.at(id);
    }
    else {
        return std::shared_ptr<Entity>();
    }
}

const std::unordered_map<Entity::Id, std::shared_ptr<Entity>> &Entity::GetAll() {
    return msEntities;
}

void Entity::Destroy(Entity::Id id) {
    msEntities.erase(id);
}

void Entity::ScheduleDestroy(Entity::Id id) {
    msScheduled.push_back(id);
}

void Entity::DestroyAll() {
    msEntities.clear();
}

void Entity::DestroyScheduled() {
    for (auto id : msScheduled) {
        Destroy(id);
    }
    msScheduled.clear();
}

void Entity::AttachComponent(std::shared_ptr<Component> component) {
    if (component->IsAttached()) {
        THROW_ERROR("Component already attached");
    }

    mComponents[component->GetType()] = component;
    component->OnAttach(std::weak_ptr<Entity>(Get(mId)));
}

std::shared_ptr<Component> Entity::GetComponent(std::string type) {
    if (mComponents.count(type)) {
        return mComponents.at(type);
    }
    else {
        return std::shared_ptr<Component>();
    }
}

void Entity::DetachComponent(std::string type) {
    if (mComponents.count(type)) {
        auto component = mComponents.at(type);
        component->OnDetach();
        mComponents.erase(type);
    }
}

void Entity::DetachAllComponents() {
    for (auto it : mComponents) {
        it.second->OnDetach();
    }
    mComponents.clear();
}

const Entity::Id &Entity::GetId() const {
    return mId;
}

Entity::Entity(Entity::Id id) :
    mId(id) {
}

Entity::~Entity() {
    DetachAllComponents();
}

const Entity::Id Entity::Invalid = 0;
Entity::Id Entity::msLastId = 0;

std::unordered_map<Entity::Id, std::shared_ptr<Entity>> Entity::msEntities;
std::list<Entity::Id> Entity::msScheduled;
