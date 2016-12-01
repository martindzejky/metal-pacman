#pragma once

#include <string>
#include <memory>

#include "NonCopyable.hpp"


/**
 * Interface for all components.
 */


class Entity;

class Component : public NonCopyable {

public:

    virtual void OnAttach(std::weak_ptr<Entity> entity);
    virtual void OnDetach();

    virtual std::string GetType() const = 0;
    bool IsAttached() const;

    virtual ~Component() = default;


private:

    bool mAttached = false;

};
