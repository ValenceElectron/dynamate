#include "ObjectLoader.hpp"

ObjectLoader::ObjectLoader(DrawableObjectManager& objManager) {
    std::cout << "Scanning default directory...\n";
    scanDefaultDirectory();
    LoadedData defaultData = loadDefaults();
    std::cout << "Data loaded, forming DrawableObject...\n\n\n";
    DrawableObject* object = deserialize(defaultData);

    addObject(objManager, object);
}

void ObjectLoader::addObject(DrawableObjectManager& objManager, DrawableObject* object) {
    objManager.addObject(object);
}

void ObjectLoader::scanDefaultDirectory() {
    std::string line = "";
    std::ifstream fileStream(defaultSceneFilePath + indexFile, std::ios::in);

    if (!fileStream.eof()) { 
        getline(fileStream, line);
    } else {
        std::cout << "Default scene is missing!\n";
        return;
    }

    if (line == "#dynamo") {
        while (!fileStream.eof()) {
            getline(fileStream, line);
            if (line != "") { defaultFileContents.push_back(line); }
        }
        std::cout << "DYNAMO!\n";
    }
}

ObjectLoader::LoadedData ObjectLoader::loadDefaults() {
    std::cout << "Loading defaults...\n\n\n";
    std::string keyValueDelimiter = ":";

    LoadedData defaultData;

    for (std::string string : defaultFileContents) {
        size_t delimPosition = string.find(keyValueDelimiter);
        std::string key = string.substr(0, delimPosition);
        std::cout << key << std::endl;
        std::string value = string.substr(delimPosition + 1, string.size() - 1);
        std::cout << value << std::endl;
        //std::cout << key << " " << value << std::endl;
        
        if (key == "numberOfVertices") { defaultData.numberOfVertices = value; }
        else if (key == "vertices") { defaultData.vertices = value; }
        else if (key == "position") { defaultData.position = value; }
        else if (key == "vertexShader") { defaultData.vertexShader = value; }
        else if (key == "fragmentShader") { defaultData.fragmentShader = value; }
        else { std::cout << "Invalid key: " << key << std::endl; }
    }

    defaultData.filePath = defaultSceneFilePath;

    return defaultData;
}

DrawableObject* ObjectLoader::deserialize(LoadedData data) {
    int numberOfVertices = 0;
    float *vertices;
    float position[3] = { 0 };
    std::string arrayElementDelimiter = ",";

    try {
        numberOfVertices = std::stoi(data.numberOfVertices);
        std::cout << "vertices: " << numberOfVertices << std::endl;

        vertices = new float[numberOfVertices];
        std::stringstream vertexStream(data.vertices);

        int i = 0;
        // i < numberOfVertices because an extra comma is added
        // in the index.txt to make this loop go smoothly. without it, stof
        // throws an error
        while (vertexStream.good() && i < numberOfVertices) {
            std::string substring = "";
            getline(vertexStream, substring, ',');
            vertices[i] = std::stof(substring);
            std::cout << "vertexStream: " << vertices[i] << std::endl;
            i++;
        }

        std::stringstream positionStream(data.position);
        i = 0;
        while (positionStream.good() && i < 3) {
            std::string substring = "";
            getline(positionStream, substring, ',');
            position[i] = std::stof(substring);
            std::cout << "position: " << position[i] << std::endl;
            i++;
        }

    } catch (const std::exception &e) {
        std::cout << "ERROR: " << e.what() << std::endl;
    }

    std::cout << "\nObject loaded!\n\n\n";

    DrawableObject* object = new DrawableObject(position, vertices, numberOfVertices);
    std::string vertexShader = data.filePath + data.vertexShader;
    std::string fragmentShader = data.filePath + data.fragmentShader;
    object->setShader(OGLSetup::createShaderProgram(vertexShader, fragmentShader));
    return object;
}
