#pragma once

#include <string>

#include "NonCopyable.hpp"


/**
 * Interface for all resources managed by the resource manager.
 */


class Resource : public NonCopyable {
    friend class Resources;

public:

    virtual void Load(std::string path) = 0;

    const std::string &GetName() const {
        return mName;
    }

    virtual ~Resource() = default;


protected:

    Resource(std::string name) : mName(name) {}


private:

    std::string mName;

};
