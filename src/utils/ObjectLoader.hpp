#ifndef OBJECTLOADER_H
#define OBJECTLOADER_H

#include <string>
#include <list>
#include <vector>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <sstream>
#include "DrawableObjectManager.hpp"
#include "OGLSetup.hpp"

class ObjectLoader {
public:
    ObjectLoader(DrawableObjectManager& objManager);

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
    std::vector<std::string> sceneDirectories;
    std::string indexFile = "index.txt";
    std::string chosenFilePath = "";

    std::list<std::string> fileContents;
    std::list<std::string>::iterator fileContentIterator;
    std::vector<LoadedData> sceneData;
    std::vector<DrawableObject*> objects;
    int numberOfObjectsInScene;
    
    void chooseScene();
    void listSceneDirectories();
    void scanDirectory();
    void loadScene();
    void deserialize();
    void addObjects(DrawableObjectManager& objManager);
};

#endif