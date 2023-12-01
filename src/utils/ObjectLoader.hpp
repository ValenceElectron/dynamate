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
