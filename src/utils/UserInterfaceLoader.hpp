/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef USERINTERFACELOADER_H
#define USERINTERFACELOADER_H

#include <string>
#include <list>
#include <vector>
#include <filesystem>
#include <fstream>
#include <sstream>
#include "Loader.hpp"
#include "../render/UserInterfaceManager.hpp"
#include "OGLSetup.hpp"

class UserInterfaceLoader : public Loader {
public:
    UserInterfaceLoader(UserInterfaceManager& uiManager, float aspRatio, int width, int height);
    void loadData();
    void deserialize();
    void addToManager(UserInterfaceManager& uiManager);

private:
    struct LoadedData {
        std::string objectType;
        std::string buttonType;
        std::string numberOfVertices;
        std::string vertices;
        std::string position;
        std::string uiBounds;
        std::string scale;
        std::string boundsScale;
        std::string filePath;
        std::string vertexShader;
        std::string fragmentShader;
    };

    std::vector<UserInterfaceElement*> elements;
    std::vector<LoadedData> loadedData;
    int windowWidth, windowHeight;
};

#endif
