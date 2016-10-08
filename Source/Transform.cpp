#include "Transform.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


void Transform::Move(float x, float y, float z, Space space) {
    Move(glm::vec3(x, y, z), space);
}

void Transform::Move(glm::vec3 pos, Space space) {
    mDirty = true;

    switch (space) {
        case Space::Local:
            mPosition += mRotation * pos;
            break;

        case Space::Global:
            mPosition += pos;
            break;
    }
}

void Transform::Pitch(float angle, Space space) {
    Rotate(glm::vec3(1.f, 0.f, 0.f), angle, space);
}

void Transform::Yaw(float angle, Space space) {
    Rotate(glm::vec3(0.f, 1.f, 0.f), angle, space);
}

void Transform::Roll(float angle, Space space) {
    Rotate(glm::vec3(0.f, 0.f, 1.f), angle, space);
}

void Transform::Rotate(glm::vec3 axis, float angle, Space space) {
    Rotate(glm::angleAxis(angle, axis), space);
}

void Transform::Rotate(glm::quat quat, Space space) {
    mDirty = true;
    glm::quat qnorm = glm::normalize(quat);

    switch (space) {
        case Space::Local:
            mRotation = mRotation * qnorm;
            break;

        case Space::Global:
            mRotation = qnorm * mRotation;
            break;
    }
}

const glm::mat4 &Transform::GetMatrix() {
    if (mDirty) {
        mDirty = false;

        glm::mat4 position = glm::translate(glm::mat4(), mPosition);
        glm::mat4 rotation = glm::mat4_cast(mRotation);

        mMatrix = position * rotation;
    }

    return mMatrix;
}

glm::mat4 Transform::GetInverse() const {
    // TODO: Why on Earth does this result in EXC_BAD_ACCESS???
    return glm::inverse(mMatrix);
}

Transform::Transform(float x, float y, float z) :
    Transform(glm::vec3(x, y, z)) {
}

Transform::Transform(glm::vec3 pos) :
    mPosition(pos) {
}
