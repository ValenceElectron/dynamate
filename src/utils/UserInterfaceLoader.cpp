#include "UserInterfaceLoader.hpp"

UserInterfaceLoader::UserInterfaceLoader(UserInterfaceManager& uiManager, float aspRatio, int width, int height)
: Loader(aspRatio) {
    filePath = "src/ui/";
    indexFile = "index.txt";
    windowWidth = width; windowHeight = height;

    scanDirectory();
    loadData();
    deserialize();
    addToManager(uiManager);
}

void UserInterfaceLoader::loadData() {
    std::cout << "Reading index.txt...\n\n\n";
    std::string keyValueDelimiter = ":";

    fileContentIterator = fileContents.begin();

    std::string numberOfObjects = *fileContentIterator;
    size_t delimPos = numberOfObjects.find(keyValueDelimiter);
    numberOfObjects = numberOfObjects.substr(delimPos + 1, numberOfObjects.size());
    numberOfObjectsInScene = std::stoi(numberOfObjects);

    std::cout << "Number of UI elements to load: " << numberOfObjectsInScene << "\n\n";

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

            if (key == "objectType") { data.objectType = value; }
            else if (key == "buttonType") { data.buttonType = value; }
            else if (key == "numberOfVertices") { data.numberOfVertices = value; }
            else if (key == "vertices") { data.vertices = value; }
            else if (key == "position") { data.position = value; }
            else if (key == "scale") { data.scale = value; }
            else if (key == "boundsScale") { data.boundsScale = value; }
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

void UserInterfaceLoader::deserialize() {
    std::string arrayElementDelimiter = ",";

    std::cout << "\n\nBeginning UI deserialization...\n\n";

    for (int i = 0; i < loadedData.size(); i++) {
        int numberOfVertices = 0;
        float *vertices;
        float position[3] = { 0 };
        double uiBounds[4] = { 0 };
        double uiBoundsScale[2] = { 0 };
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

            std::stringstream boundsScaleStream(data.boundsScale);
            i = 0;
            while (boundsScaleStream.good() && i < 2) {
                std::string substring = "";
                getline(boundsScaleStream, substring, ',');
                uiBoundsScale[i] = std::stod(substring);
                std::cout << "UI Bounds Scale: " << uiBoundsScale[i] << std::endl;
                i++;
            }

        } catch (const std::exception &e) {
            std::cout << "ERROR: " << e.what() << std::endl;
        }

        float objectScale = std::stof(data.scale);

        double conversionFactorX = (position[0] / 10.0f);
        double conversionFactorY = (position[1] / 10.0f);

        // Half-width of square if using vertices between -0.5 and 0.5.
        double uiScaleX = objectScale * uiBoundsScale[0];
        double uiScaleY = objectScale * uiBoundsScale[1];
        double boundsModifierX = ((windowWidth / (5 * aspectRatio)) * uiScaleX) / 2;
        double boundsModifierY = ((windowWidth / (5 * aspectRatio)) * uiScaleY) / 2;

        std::cout << "Bounds Modifier: (" << boundsModifierX << ", " << boundsModifierY << ")" << std::endl;

        // Adjust the dynamo x-coordinate and map it to within the range afforded by the projectionMatrix
        position[0] = (position[0] / 2.0f) * aspectRatio;
        // Also adjust the y-coordinate and map it to within the range afforded by the projectionMatrix
        position[1] = (position[1] / 2.0f);

        uiBounds[0] = ((double) windowWidth * conversionFactorX) - boundsModifierX;
        uiBounds[1] = ((double) windowWidth * conversionFactorX) + boundsModifierX;
        uiBounds[2] = ((double) windowHeight - ((double) windowHeight * conversionFactorY)) - boundsModifierY;
        uiBounds[3] = ((double) windowHeight - ((double) windowHeight * conversionFactorY)) + boundsModifierY;

        std::cout << "x bounds: ( " << uiBounds[0] << ", " << uiBounds[1] << ")\n";
        std::cout << "y bounds: ( " << uiBounds[2] << ", " << uiBounds[3] << ")\n";
        
        UserInterfaceElement* element;
        if (data.buttonType == "main_menu") {
            std::cout << "Main menu button\n";
            element = new MainMenuButton(data.objectType, position, objectScale, vertices, numberOfVertices, uiBounds);
        } else {
            element = new UserInterfaceElement(data.objectType, position, objectScale, vertices, numberOfVertices, uiBounds);
        }
        element->setShader(OGLSetup::createShaderProgram(vertexShader, fragmentShader));
        elements.push_back(element);
        //std::cout << "\nObject loaded!\n";
    }

    std::cout << "\nUI deserialization finished!\n\n\n";
}

void UserInterfaceLoader::addToManager(UserInterfaceManager& uiManager) {
    for (UserInterfaceElement* element : elements) {
        uiManager.addToBuffer(element);
    }
}
