#pragma once

#include <string>
#include <functional>
#include <unordered_map>

#include "Singleton.hpp"


/**
 * The global events center. Helps with decoupling and communication.
 * Listen to and fire events right here.
 * TODO: Add tests
 */


class Events : public Singleton<Events> {

public:

    typedef unsigned int ListenerId;
    typedef std::function<void(void *)> Listener;


public:

    static void Create();

    ListenerId AddListener(std::string event, Listener listener);
    void RemoveListener(std::string event, ListenerId listenerId);

    void FireEvent(std::string event, void *data = nullptr);


private:

    ListenerId mLastId = 0;
    std::unordered_map<std::string, std::unordered_map<ListenerId, Listener>> mListeners;

};
