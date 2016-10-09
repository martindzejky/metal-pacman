#include "Component.hpp"


void Component::OnAttach(std::weak_ptr<Entity> entity) {
    mAttached = true;
}

void Component::OnDetach() {
    mAttached = false;
}

bool Component::IsAttached() const {
    return mAttached;
}
