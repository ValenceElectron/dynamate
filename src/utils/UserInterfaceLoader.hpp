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
    UserInterfaceLoader(UserInterfaceManager& uiManager, float aspRatio);
    void loadData();
    void deserialize();
    void addToManager(UserInterfaceManager& uiManager);

private:
    struct LoadedData {
        std::string objectType;
        std::string numberOfVertices;
        std::string vertices;
        std::string position;
        std::string uiBounds;
        std::string scale;
        std::string filePath;
        std::string vertexShader;
        std::string fragmentShader;
    };

    std::vector<UserInterfaceElement*> elements;
    std::vector<LoadedData> loadedData;
};

#endif
