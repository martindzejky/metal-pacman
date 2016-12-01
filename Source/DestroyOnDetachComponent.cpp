#include "DestroyOnDetachComponent.hpp"

#include "Entity.hpp"
#include "State.hpp"


std::string DestroyOnDetachComponent::GetType() const {
    return "DestroyOnDetachComponent";
}

void DestroyOnDetachComponent::OnDetach() {
    Component::OnDetach();

    if (State::Current()->IsRunning()) {
        Entity::Destroy(mId);
    }
}

DestroyOnDetachComponent::DestroyOnDetachComponent(Entity::Id id) : mId(id) {}
