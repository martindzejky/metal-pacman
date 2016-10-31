#include "Resources.hpp"

#include "Error.hpp"
#include "Shader.hpp"
#include "ModelData.hpp"
#include "Texture.hpp"


void Resources::Create() {
    SetSingleton(std::make_shared<Resources>());
}

std::shared_ptr<Resource> Resources::Load(std::string name, std::string path) {
    // TODO: Add resource loaders
    auto resource = std::shared_ptr<Resource>();
    auto ext = path.substr(path.find_last_of('.') + 1);

    if (ext == "glsl") {
        Shader::Type type = Shader::Type::Vertex;
        if (path.find("Fragment") != std::string::npos) {
            type = Shader::Type::Fragment;
        }

        resource = std::make_shared<Shader>(name, type);
        resource->Load(path);
    }
    else if (ext == "ply") {
        resource = std::make_shared<ModelData>(name);
        resource->Load(path);
    }
    else if (ext == "png") {
        resource = std::make_shared<Texture>(name);
        resource->Load(path);
    }

    if (resource) {
        mResources[name] = resource;
    }

    return resource;
}

void Resources::UnloadAll() {
    mResources.clear();
}

std::shared_ptr<Resource> Resources::GetResource(std::string name) {
    if (mResources.count(name)) {
        return mResources[name];
    }
    else {
        THROW_ERROR(std::string("Resource not loaded: ") + name);
    }
}
