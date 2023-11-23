#ifndef UILOADER_H
#define UILOADER_H

#include "Loader.hpp"
#include "../render/DrawableObjectManager.hpp"

class UILoader : public Loader {
public:
    UILoader(float aspRatio);
    void loadData();
    void deserialize();
    void addToManager();

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
