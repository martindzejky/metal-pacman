#pragma once

#include <string>

#include "Component.hpp"
#include "Events.hpp"


/**
 * Renders a model.
 */


class ArrayObject;

class BufferObject;

class Entity;

class Resource;

class ModelComponent : public Component {

public:

    virtual void OnAttach(std::weak_ptr<Entity> entity) override;
    virtual void OnDetach() override;
    virtual std::string GetType() const override;

    void OnRender();
    void OnShadow();

    ModelComponent(std::string modelName, std::string textureName = "BlankDiffuseTexture",
                   std::string normalMapName = "BlankNormalTexture",
                   std::string reflectionMapName = "BlankReflectionTexture",
                   float emission = 0);


private:

    std::shared_ptr<ArrayObject> mArrayObject;
    std::shared_ptr<ArrayObject> mShadowArrayObject;

    std::shared_ptr<BufferObject> mVertices;
    std::shared_ptr<BufferObject> mNormals;
    std::shared_ptr<BufferObject> mColors;
    std::shared_ptr<BufferObject> mTexCoords;
    std::shared_ptr<BufferObject> mTangents;
    std::shared_ptr<BufferObject> mIndices;
    unsigned int mIndexNumber = 0;

    std::weak_ptr<Entity> mEntity;
    Events::ListenerId mRenderListenerId;
    Events::ListenerId mShadowListenerId;

    std::shared_ptr<Resource> mTexture;
    std::shared_ptr<Resource> mNormalMap;
    std::shared_ptr<Resource> mReflectionMap;

    float mEmission = 0;

};


