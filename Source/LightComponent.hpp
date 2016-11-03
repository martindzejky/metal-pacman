#pragma once

#include <list>

#include "Component.hpp"
#include "Events.hpp"


/**
 * Makes the entity cast light.
 */


class Entity;
class FrameBuffer;

class LightComponent : public Component {

public:

    virtual void OnAttach(std::weak_ptr<Entity> entity) override;
    virtual void OnDetach() override;
    virtual std::string GetType() const override;

    void OnUpdate();
    void OnShadowMaps();

    LightComponent(float r, float g, float b, float radius);


private:

    static std::list<LightComponent*> msLightList;

    const static unsigned int msShadowMapWidth;
    const static unsigned int msShadowMapHeight;

    std::weak_ptr<Entity> mEntity;
    Events::ListenerId mUpdateListenerId;
    Events::ListenerId mShadowsListenerId;

    std::shared_ptr<FrameBuffer> mShadowMap;

    float mRed;
    float mGreen;
    float mBlue;
    float mRadius;

};


