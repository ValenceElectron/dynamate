#include "ObjectLoader.hpp"

ObjectLoader::ObjectLoader(DrawableObjectManager& objManager) {
    listSceneDirectories();
    chooseScene();
    scanDirectory();
    LoadedData defaultData = loadScene();
    DrawableObject* object = deserialize(defaultData);

    addObject(objManager, object);
}


void ObjectLoader::addObject(DrawableObjectManager& objManager, DrawableObject* object) {
    objManager.addObject(object);
}

void ObjectLoader::chooseScene() {
    int directoryIndex;
    std::cout << "\n\n\nWhich scene would you like to load?\n\n";

    for (int i = 1; i <= sceneDirectories.size(); i++) {
        std::cout << i << ". " << sceneDirectories.at(i - 1) << std::endl;
    }

    std::cout << "\033[9999;1H";
    std::cout << "Enter 1-" << sceneDirectories.size() << ": ";
    std::cin >> directoryIndex;

    if (!(directoryIndex > 0) && !(directoryIndex <= sceneDirectories.size())) {
        std::cout << "ERROR: \"" << directoryIndex << "\" is not a valid option\n";
        std::cout << "Resorting to default scene...\n";
        directoryIndex -1;
    }

    if (directoryIndex == -1) { chosenFilePath = defaultSceneFilePath; }
    else { chosenFilePath = sceneDirectories.at(directoryIndex - 1) + "/"; }
}

void ObjectLoader::listSceneDirectories() {
    for (auto& element : std::filesystem::directory_iterator(sceneDirectory)) {
        if (element.is_directory()) { sceneDirectories.push_back(element.path().string()); }
    }
}

void ObjectLoader::scanDirectory() {
    std::string line = "";

    std::ifstream fileStream(chosenFilePath + indexFile, std::ios::in);

    if (!fileStream.eof()) { 
        getline(fileStream, line);
    } else {
        std::cout << "Scene is missing!\n";
        return;
    }

    if (line == "#dynamo") {
        while (!fileStream.eof()) {
            getline(fileStream, line);
            std::cout << line << std::endl;
            if (line != "") { fileContents.push_back(line); }
        }
        std::cout << "DYNAMO!\n";
    }
}

ObjectLoader::LoadedData ObjectLoader::loadScene() {
    std::cout << "Reading index.txt...\n\n\n";
    std::string keyValueDelimiter = ":";
    LoadedData data;

    for (std::string string : fileContents) {
        size_t delimPosition = string.find(keyValueDelimiter);
        std::string key = string.substr(0, delimPosition);
        std::string value = string.substr(delimPosition + 1, string.size() - 1);
        //std::cout << key << " " << value << std::endl;
        
        if (key == "numberOfVertices") { data.numberOfVertices = value; }
        else if (key == "vertices") { data.vertices = value; }
        else if (key == "position") { data.position = value; }
        else if (key == "vertexShader") { data.vertexShader = value; }
        else if (key == "fragmentShader") { data.fragmentShader = value; }
        else { std::cout << "Invalid key: " << key << std::endl; }
    }

    data.filePath = chosenFilePath;

    return data;
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
