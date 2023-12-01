#include "ObjectLoader.hpp"

ObjectLoader::ObjectLoader(DrawableObjectManager& objManager, float aspRatio)
: Loader(aspRatio) {
    filePath = "scenes/default/";
    indexFile = "index.txt";

    scanDirectory();
    loadData();
    deserialize();
    addToManager(objManager);
}

void ObjectLoader::loadData() {
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
        fileContentIterator++;
        std::cout << "Extracting object " << i + 1 << " data...\n";

        while (*fileContentIterator != "endObject" && fileContentIterator != fileContents.end()) {
            std::string string = *fileContentIterator;
            size_t delimPosition = string.find(keyValueDelimiter);
            std::string key = string.substr(0, delimPosition);
            std::string value = string.substr(delimPosition + 1, string.size() - 1);
            std::cout << key << " " << value << std::endl;

            if (key == "numberOfVertices") { data.numberOfVertices = value; }
            else if (key == "vertices") { data.vertices = value; }
            else if (key == "position") { data.position = value; }
            else if (key == "scale") { data.scale = value; }
            else if (key == "vertexShader") { data.vertexShader = value; }
            else if (key == "fragmentShader") { data.fragmentShader = value; }
            else if (key == "\n") { }
            else if (key == "\0") { }
            else { std::cout << "Invalid key: " << key << std::endl; }

            fileContentIterator++;
        }

        data.filePath = filePath;
        loadedData.push_back(data);
        std::cout << "Object data loaded!\n";
    }
}

void ObjectLoader::deserialize() {
    std::string arrayElementDelimiter = ",";

    std::cout << "\n\nBeginning deserialization...\n\n";

    for (int i = 0; i < loadedData.size(); i++) {
        int numberOfVertices = 0;
        float *vertices;
        float position[3] = { 0 };
        LoadedData data = loadedData.at(i);
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
        // Adjust the y-coordinate to also map within the range afforded by the projectionMatrix
        position[1] = (position[1] / 2.0f);

        DrawableObject* object = new DrawableObject("drawable", position, objectScale, vertices, numberOfVertices);
        object->setShader(OGLSetup::createShaderProgram(vertexShader, fragmentShader));
        objects.push_back(object);
        //std::cout << "\nObject loaded!\n";
    }

    std::cout << "\nDeserialization finished!\n\n\n";
}

void ObjectLoader::addToManager(DrawableObjectManager& objManager) {
    for (DrawableObject* object : objects) {
        objManager.addToBuffer(object);
    }
}

