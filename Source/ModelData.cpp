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

    // normalize or create colors
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

    // calculate tangent
    mTangents.reserve(mVertices.size());
    for (auto i = 0; i < mIndices.size() / 3; ++i) {
        // indices
        auto i1 = mIndices[i * 3 + 0];
        auto i2 = mIndices[i * 3 + 1];
        auto i3 = mIndices[i * 3 + 2];

        // vertex positions
        auto v1x = mVertices[i1 * 3 + 0];
        auto v1y = mVertices[i1 * 3 + 1];
        auto v1z = mVertices[i1 * 3 + 2];
        auto v2x = mVertices[i2 * 3 + 0];
        auto v2y = mVertices[i2 * 3 + 1];
        auto v2z = mVertices[i2 * 3 + 2];
        auto v3x = mVertices[i3 * 3 + 0];
        auto v3y = mVertices[i3 * 3 + 1];
        auto v3z = mVertices[i3 * 3 + 2];

        // vertex tex coords
        auto v1u = mTexCoords[i1 * 2 + 0];
        auto v1v = mTexCoords[i1 * 2 + 1];
        auto v2u = mTexCoords[i2 * 2 + 0];
        auto v2v = mTexCoords[i2 * 2 + 1];
        auto v3u = mTexCoords[i3 * 2 + 0];
        auto v3v = mTexCoords[i3 * 2 + 1];

        float x1 = v2x - v1x;
        float x2 = v3x - v1x;
        float y1 = v2y - v1y;
        float y2 = v3y - v1y;
        float z1 = v2z - v1z;
        float z2 = v3z - v1z;

        float s1 = v2u - v1u;
        float s2 = v3u - v1u;
        float t1 = v2v - v1v;
        float t2 = v3v - v1v;

        float r = 1.f / (s1 * t2 - s2 * t1);
        float sdirx = (t2 * x1 - t1 * x2) * r;
        float sdiry = (t2 * y1 - t1 * y2) * r;
        float sdirz = (t2 * z1 - t1 * z2) * r;

        mTangents.push_back(sdirx);
        mTangents.push_back(sdiry);
        mTangents.push_back(sdirz);
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

const std::vector<float> &ModelData::GetTangents() const {
    return mTangents;
}

const std::vector<unsigned int> &ModelData::GetIndices() const {
    return mIndices;
}

ModelData::ModelData(std::string name) : Resource(name) {}
