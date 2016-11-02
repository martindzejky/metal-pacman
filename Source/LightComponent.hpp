#pragma once

#include <list>

#include "Component.hpp"
#include "Events.hpp"


/**
 * Makes the entity cast light.
 */


class Entity;

class LightComponent : public Component {

public:

    virtual void OnAttach(std::weak_ptr<Entity> entity) override;
    virtual void OnDetach() override;
    virtual std::string GetType() const override;

    void OnUpdate();

    LightComponent(float r, float g, float b, float radius);


private:

    static std::list<LightComponent*> msLightList;

    std::weak_ptr<Entity> mEntity;
    Events::ListenerId listenerId;

    float mRed;
    float mGreen;
    float mBlue;
    float mRadius;

};


