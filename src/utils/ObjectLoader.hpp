/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef OBJECTLOADER_H
#define OBJECTLOADER_H

#include <string>
#include <list>
#include <vector>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <sstream>
#include "Loader.hpp"
#include "../render/DrawableObjectManager.hpp"
#include "OGLSetup.hpp"

class ObjectLoader : public Loader {
public:
    ObjectLoader(DrawableObjectManager& objManager, float aspectRatio);

    void loadData();
    void deserialize();
    void addToManager(DrawableObjectManager& objManager);

private:
    struct LoadedData {
        std::string numberOfVertices;
        std::string vertices;
        std::string position;
        std::string scale;
        std::string filePath;
        std::string vertexShader;
        std::string fragmentShader;
    };

    std::vector<LoadedData> loadedData;
    std::vector<DrawableObject*> objects;
};

#endif
