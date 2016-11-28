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

void Transform::Rotate(Transform::Axis axis, float angle, Transform::Space space) {
    switch (axis) {
        case Axis::X:
            Pitch(angle, space);
            break;

        case Axis::Y:
            Yaw(angle, space);
            break;

        case Axis::Z:
            Roll(angle, space);
            break;
    }
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

void Transform::Scale(float x, float y, float z) {
    mDirty = true;
    mScale *= glm::vec3(x, y, z);
}

void Transform::Scale(float s) {
    mDirty = true;
    mScale *= glm::vec3(s, s, s);
}

void Transform::SetPosition(float x, float y, float z) {
    mDirty = true;
    mPosition = glm::vec3(x, y, z);
}

void Transform::Attach(std::shared_ptr<Transform> parent) {
    mParent = parent;
}

void Transform::Detach() {
    mParent = std::shared_ptr<Transform>();
}

const glm::vec3 &Transform::GetPosition() const {
    return mPosition;
}

const glm::mat4 &Transform::GetMatrix() {
    if (mDirty) {
        glm::mat4 position = glm::translate(glm::mat4(), mPosition);
        glm::mat4 rotation = glm::mat4_cast(mRotation);
        glm::mat4 scale = glm::scale(glm::mat4(), mScale);

        mMatrix = position * rotation * scale;
        ++mVersion;
    }

    if (mParent) {
        if (mDirty || mParent->GetVersion() != mParentVersion) {
            mParentVersion = mParent->GetVersion();
            mMatrixWithParent = mParent->GetMatrix() * mMatrix;
        }
    }
    else {
        return mMatrix;
    }

    mDirty = false;

    return mMatrixWithParent;
}

unsigned long Transform::GetVersion() const {
    return mVersion;
}

Transform::Transform() :
    Transform(0, 0, 0) {
}

Transform::Transform(float x, float y, float z) :
    Transform(glm::vec3(x, y, z)) {
}

Transform::Transform(glm::vec3 pos) :
    mPosition(pos), mScale(1, 1, 1) {
}
