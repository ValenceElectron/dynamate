#ifndef OBJECTLOADER_H
#define OBJECTLOADER_H

#include <string>
#include <list>
#include <iostream>
#include <fstream>
#include <sstream>
#include "DrawableObjectManager.hpp"
#include "OGLSetup.hpp"

class ObjectLoader {
public:
    ObjectLoader(DrawableObjectManager& objManager);
    void addObject(DrawableObjectManager& objManager, DrawableObject* object);

    struct LoadedData {
        std::string numberOfVertices;
        std::string vertices;
        std::string position;
        std::string filePath;
        std::string vertexShader;
        std::string fragmentShader;
    };

private:
    std::string sceneDirectory = "scenes/";
    std::string defaultSceneFilePath = "scenes/default/";
    std::string indexFile = "index.txt";

    std::list<std::string> defaultFileContents;
    
    void scanDefaultDirectory();
    LoadedData loadDefaults();
    DrawableObject* deserialize(LoadedData data);
};

#endif
