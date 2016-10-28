#pragma once

#include <string>

#include "Component.hpp"
#include "Events.hpp"


/**
 * Renders a model.
 */


class ArrayObject;
class BufferObject;
class ShaderProgram;
class Entity;

class ModelComponent : public Component {

public:

    virtual void OnAttach(std::weak_ptr<Entity> entity) override;
    virtual void OnDetach() override;
    virtual std::string GetType() const override;

    void OnRender();

    ModelComponent(std::string modelName, std::shared_ptr<ShaderProgram> shaderProgram);


private:

    std::shared_ptr<ArrayObject> mArrayObject;
    std::shared_ptr<BufferObject> mVertices;
    std::shared_ptr<BufferObject> mColors;
    std::shared_ptr<BufferObject> mIndices;
    unsigned int mIndexNumber = 0;

    std::shared_ptr<ShaderProgram> mShaderProgram;
    std::weak_ptr<Entity> mEntity;
    Events::ListenerId mListenerId;

};


