#pragma once


#include <glm/fwd.hpp>
#include <glm/vec3.hpp>
#include <glm/gtc/quaternion.hpp>


/**
 * Transform defines an object's position and orientation in space. It uses
 * vectors and quaternions to store the state. It can also easily made into
 * a matric and passed to OpenGL.
 */


class Transform {

public:

    enum class Space {
        Local,
        Global
    };


public:

    void Move(float x, float y, float z, Space space = Space::Local);
    void Move(glm::vec3 pos, Space space = Space::Local);

    void Pitch(float angle, Space space = Space::Local);
    void Yaw(float angle, Space space = Space::Local);
    void Roll(float angle, Space space = Space::Local);
    void Rotate(glm::vec3 axis, float angle, Space space = Space::Local);
    void Rotate(glm::quat quat, Space space = Space::Local);

    glm::mat4 GetMatrix() const;
    glm::mat4 GetInverse() const;

    Transform() = default;
    Transform(float x, float y, float z);
    Transform(glm::vec3 pos);


private:

    glm::vec3 mPosition;
    glm::quat mRotation;

};
