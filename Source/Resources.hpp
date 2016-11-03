#pragma once

#include <string>
#include <memory>
#include <unordered_map>

#include "Singleton.hpp"
#include "Resource.hpp"


/**
 * Global resource manager. Loads game resources like textures and models
 * from the disk drive.
 */


class Resources : public Singleton<Resources> {

public:

    static void Create();

    std::shared_ptr<Resource> Load(std::string name, std::string path);
    void UnloadAll();

    std::shared_ptr<Resource> GetResource(std::string name);


private:

    std::unordered_map<std::string, std::shared_ptr<Resource>> mResources;

};


