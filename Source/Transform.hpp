#pragma once


#include <memory>

#include <glm/fwd.hpp>
#include <glm/vec3.hpp>
#include <glm/gtc/quaternion.hpp>


/**
 * Transform defines an object's position and orientation in space. It uses
 * vectors and quaternions to store the state. It can also easily made into
 * a matrix and passed to OpenGL.
 */


class Transform {

public:

    enum class Space {
        Local,
        Global
    };

    enum class Axis {
        X,
        Y,
        Z
    };


public:

    void Move(float x, float y, float z, Space space = Space::Local);
    void Move(glm::vec3 pos, Space space = Space::Local);

    void Pitch(float angle, Space space = Space::Local);
    void Yaw(float angle, Space space = Space::Local);
    void Roll(float angle, Space space = Space::Local);
    void Rotate(glm::vec3 axis, float angle, Space space = Space::Local);
    void Rotate(Axis axis, float angle, Space space = Space::Local);
    void Rotate(glm::quat quat, Space space = Space::Local);

    void Scale(float x, float y, float z);
    void Scale(float s);

    void Attach(std::shared_ptr<Transform> parent);
    void Detach();

    const glm::vec3 &GetPosition() const;
    const glm::mat4 &GetMatrix();

    Transform();
    Transform(float x, float y, float z);
    Transform(glm::vec3 pos);


private:

    glm::vec3 mPosition;
    glm::quat mRotation;
    glm::vec3 mScale;
    glm::mat4 mMatrix;

    bool mDirty = true;

    std::shared_ptr<Transform> mParent;
    glm::mat4 mMatrixWithParent;

};
