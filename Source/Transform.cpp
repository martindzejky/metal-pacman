#include "Transform.hpp"

#include <glm/gtc/matrix_transform.hpp>


void Transform::Move(float x, float y, float z, Space space) {
    Move(glm::vec3(x, y, z), space);
}

void Transform::Move(const glm::vec3 &pos, Space space) {
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
    Rotate(glm::vec3(1.0f, 0.0f, 0.0f), angle, space);
}

void Transform::Yaw(float angle, Space space) {
    Rotate(glm::vec3(0.0f, 1.0f, 0.0f), angle, space);
}

void Transform::Roll(float angle, Space space) {
    Rotate(glm::vec3(0.0f, 0.0f, 1.0f), angle, space);
}

void Transform::Rotate(const glm::vec3 &axis, float angle, Space space) {
    Rotate(glm::angleAxis(angle, axis), space);
}

void Transform::Rotate(const glm::quat &quat, Space space) {
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

glm::mat4 Transform::GetMatrix() const {
    glm::mat4 position = glm::translate(glm::mat4(), mPosition);
    glm::mat4 rotation = glm::mat4_cast(mRotation);

    return position * rotation;
}

glm::mat4 Transform::GetInverse() const {
    return glm::inverse(GetMatrix());
}

Transform::Transform(float x, float y, float z) :
    Transform(glm::vec3(x, y, z)) {
}

Transform::Transform(const glm::vec3 &pos) :
    mPosition(pos) {
}
