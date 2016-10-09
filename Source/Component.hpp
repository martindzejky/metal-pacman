#pragma once

#include <string>
#include <memory>


/**
 * Interface for all components.
 */


class Entity;

class Component {

public:

    virtual void OnAttach(std::weak_ptr<Entity> entity);
    virtual void OnDetach();

    virtual std::string GetType() const = 0;
    bool IsAttached() const;

    virtual ~Component() = 0;


private:

    bool mAttached = false;

};
