#include "Events.hpp"


void Events::Create() {
    SetSingleton(std::make_shared<Events>());
}

Events::ListenerId Events::AddListener(std::string event, Events::Listener listener) {
    auto id = ++mLastId;
    mListeners[event][id] = listener;
    return id;
}

void Events::RemoveListener(std::string event, Events::ListenerId listenerId) {
    mListeners[event].erase(listenerId);
}

void Events::FireEvent(std::string event, void *data) {
    for (auto listener : mListeners[event]) {
        listener.second(data);
    }
}
