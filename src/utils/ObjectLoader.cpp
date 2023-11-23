#include "ObjectLoader.hpp"

ObjectLoader::ObjectLoader(DrawableObjectManager& objManager, float aspRatio) {
    aspectRatio = aspRatio;

    // Do these calls once to load up the scene specified by the user, then another time
    // using chosenFilePath = "src/ui/" to load up the ui.
    listSceneDirectories();
    chooseScene();
    scanDirectory();
    loadScene();
    deserialize();
    addObjects(objManager);

    prepareForLoadingUI();
    scanDirectory();
    loadScene();
    deserializeUI();
    addUIElements(objManager);
}

void ObjectLoader::prepareForLoadingUI() {
    chosenFilePath = "src/ui/";
    fileContents.clear();
    sceneData.clear();
    objects.clear();
    numberOfObjectsInScene = 0;
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
            //std::cout << line << std::endl;
            fileContents.push_back(line);
        }
        std::cout << "DYNAMO!\n";
    }
}

void ObjectLoader::loadScene() {
    std::cout << "Reading index.txt...\n\n\n";
    std::string keyValueDelimiter = ":";
    
    fileContentIterator = fileContents.begin();

    std::string numberOfObjects = *fileContentIterator;
    size_t delimPos = numberOfObjects.find(keyValueDelimiter);
    numberOfObjects = numberOfObjects.substr(delimPos + 1, numberOfObjects.size());
    numberOfObjectsInScene = std::stoi(numberOfObjects);

    std::cout << "Number of objects to load: " << numberOfObjectsInScene << "\n\n";

    fileContentIterator++;

    for (int i = 0; i < numberOfObjectsInScene; i++) {
        LoadedData data;
        data.objectType = "drawable"; //objectType currently only used for UserInterfaceElement. This is here to not cause DrawableObject errors
        fileContentIterator++;
        std::cout << "Extracting object " << i + 1 << " data...\n";

        while (*fileContentIterator != "endObject" && fileContentIterator != fileContents.end()) {
            std::string string = *fileContentIterator;
            size_t delimPosition = string.find(keyValueDelimiter);
            std::string key = string.substr(0, delimPosition);
            std::string value = string.substr(delimPosition + 1, string.size() - 1);
            std::cout << key << " " << value << std::endl;

            if (key == "objectType") { data.objectType = value; }
            else if (key == "numberOfVertices") { data.numberOfVertices = value; }
            else if (key == "vertices") { data.vertices = value; }
            else if (key == "position") { data.position = value; }
            else if (key == "uiBounds") { data.uiBounds = value; }
            else if (key == "scale") { data.scale = value; }
            else if (key == "vertexShader") { data.vertexShader = value; }
            else if (key == "fragmentShader") { data.fragmentShader = value; }
            else if (key == "\n") { }
            else if (key == "\0") { }
            else { std::cout << "Invalid key: " << key << std::endl; }

            fileContentIterator++;
        }

        data.filePath = chosenFilePath;
        sceneData.push_back(data);
        std::cout << "Object data loaded!\n";
    }
}

void ObjectLoader::deserialize() {
    std::string arrayElementDelimiter = ",";

    std::cout << "\n\nBeginning deserialization...\n\n";

    for (int i = 0; i < sceneData.size(); i++) {
        int numberOfVertices = 0;
        float *vertices;
        float position[3] = { 0 };
        LoadedData data = sceneData.at(i);
        std::string vertexShader = data.filePath + data.vertexShader;
        std::string fragmentShader = data.filePath + data.fragmentShader;
        
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

        float objectScale = std::stof(data.scale);

        // Adjust the dynamo x-coordinate and map it to within the range afforded by the projectionMatrix
        position[0] = (position[0] / 2.0f) * aspectRatio;

        DrawableObject* object = new DrawableObject(data.objectType, position, objectScale, vertices, numberOfVertices);
        object->setShader(OGLSetup::createShaderProgram(vertexShader, fragmentShader));
        objects.push_back(object);
        //std::cout << "\nObject loaded!\n";
    }

    std::cout << "\nDeserialization finished!\n\n\n";
}

void ObjectLoader::deserializeUI() {
    std::string arrayElementDelimiter = ",";

    std::cout << "\n\nBeginning UI deserialization...\n\n";

    for (int i = 0; i < sceneData.size(); i++) {
        int numberOfVertices = 0;
        float *vertices;
        float position[3] = { 0 };
        double uiBounds[4] = { 0 };
        LoadedData data = sceneData.at(i);
        std::string vertexShader = data.filePath + data.vertexShader;
        std::string fragmentShader = data.filePath + data.fragmentShader;
        
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

            std::stringstream uiBoundsStream(data.uiBounds);
            i = 0;
            while(uiBoundsStream.good() && i < 4) {
                std::string substring = "";
                getline(uiBoundsStream, substring, ',');
                uiBounds[i] = std::stod(substring);
                std::cout << "UI boundary: " << uiBounds[i] << std::endl;
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

        float objectScale = std::stof(data.scale);

        // Adjust the dynamo x-coordinate and map it to within the range afforded by the projectionMatrix
        position[0] = (position[0] / 2.0f) * aspectRatio;
        // Also adjust the y-coordinate and map it to within the range afforded by the projectionMatrix
        position[1] = (position[1] / 2.0f);
        
        UserInterfaceElement* element = new UserInterfaceElement(data.objectType, position, objectScale, vertices, numberOfVertices, uiBounds);
        element->setShader(OGLSetup::createShaderProgram(vertexShader, fragmentShader));
        elements.push_back(element);
        //std::cout << "\nObject loaded!\n";
    }

    std::cout << "\nUI deserialization finished!\n\n\n";
}

void ObjectLoader::addObjects(DrawableObjectManager& objManager) {
    for (DrawableObject* object : objects) {
        objManager.addObject(object);
    }
}

void ObjectLoader::addUIElements(DrawableObjectManager& objManager) {
    for (UserInterfaceElement* element : elements) {
        objManager.addElement(element);
    }
}
