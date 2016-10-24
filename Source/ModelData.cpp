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

    plyFile.request_properties_from_element("vertex", { "x", "y", "z" }, mVertices);
    plyFile.request_properties_from_element("vertex", { "nx", "ny", "nz" }, mNormals);
    plyFile.request_properties_from_element("vertex", { "red", "green", "blue" }, mColors);
    plyFile.request_properties_from_element("face", { "vertex_indices" }, mIndices, 3);

    plyFile.read(file);
}

const std::vector<float> &ModelData::GetVertices() const {
    return mVertices;
}

const std::vector<float> &ModelData::GetNormals() const {
    return mNormals;
}

const std::vector<unsigned char> &ModelData::GetColors() const {
    return mColors;
}

const std::vector<unsigned int> &ModelData::GetIndices() const {
    return mIndices;
}

ModelData::ModelData(std::string name) : Resource(name) {}
