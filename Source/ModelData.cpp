#include "ModelData.hpp"

#include <fstream>

#include "../Libraries/tinyply.h"
#include "Error.hpp"


void ModelData::Load(std::string path) {
    std::ifstream file(path);

    if (!file.is_open()) {
        THROW_ERROR(std::string("Could not find a model file: ") + path);
    }

    tinyply::PlyFile plyFile(file);
    std::vector<unsigned char> rawColors;

    plyFile.request_properties_from_element("vertex", { "x", "y", "z" }, mVertices);
    plyFile.request_properties_from_element("vertex", { "nx", "ny", "nz" }, mNormals);
    plyFile.request_properties_from_element("vertex", { "red", "green", "blue" }, rawColors);
    plyFile.request_properties_from_element("vertex", { "s", "t" }, mTexCoords);
    plyFile.request_properties_from_element("face", { "vertex_indices" }, mIndices, 3);

    plyFile.read(file);

    if (rawColors.size() > 0) {
        // convert from [0-256] to [0-1] which is what OpenGL expects
        mColors.reserve(rawColors.size());
        for (auto c : rawColors) {
            mColors.push_back((float) c / 255);
        }
    }
    else {
        mColors.resize(mVertices.size(), 1);
    }
}

const std::vector<float> &ModelData::GetVertices() const {
    return mVertices;
}

const std::vector<float> &ModelData::GetNormals() const {
    return mNormals;
}

const std::vector<float> &ModelData::GetColors() const {
    return mColors;
}

const std::vector<float> &ModelData::GetTexCoords() const {
    return mTexCoords;
}

const std::vector<unsigned int> &ModelData::GetIndices() const {
    return mIndices;
}

ModelData::ModelData(std::string name) : Resource(name) {}
