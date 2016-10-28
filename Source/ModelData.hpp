#pragma once

#include <vector>

#include "Resource.hpp"


/**
 * This resource represents a loaded PLY model.
 */


class ModelData : public Resource {

public:

    virtual void Load(std::string path) override;

    const std::vector<float> &GetVertices() const;
    const std::vector<float> &GetNormals() const;
    const std::vector<float> &GetColors() const;
    const std::vector<unsigned int> &GetIndices() const;

    ModelData(std::string name);


private:

    std::vector<float> mVertices;
    std::vector<float> mNormals;
    std::vector<float> mColors;
    std::vector<unsigned int> mIndices;

};


