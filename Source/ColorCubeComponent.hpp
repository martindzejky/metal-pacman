#pragma once

#include "Component.hpp"
#include "Events.hpp"


/**
 * Colorful cube model.
 */


class ArrayObject;
class BufferObject;
class ShaderProgram;
class Entity;

class ColorCubeComponent : public Component {

public:

    virtual void OnAttach(std::weak_ptr<Entity> entity) override;
    virtual void OnDetach() override;
    virtual std::string GetType() const override;

    void OnRender();

    ColorCubeComponent(float size, std::shared_ptr<ShaderProgram> shaderProgram);


private:

    void CopyVertices(float size);
    void CopyColors();
    void CopyIndices();


private:

    std::shared_ptr<ArrayObject> mArrayObject;
    std::shared_ptr<BufferObject> mVertices;
    std::shared_ptr<BufferObject> mColors;
    std::shared_ptr<BufferObject> mIndices;

    std::shared_ptr<ShaderProgram> mShaderProgram;
    std::weak_ptr<Entity> mEntity;
    Events::ListenerId listenerId;

};


