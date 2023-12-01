#include "Loader.hpp"

Loader::Loader(float aspRatio) {
    aspectRatio = aspRatio;
}

void Loader::scanDirectory() {
    std::string line = "";

    std::ifstream fileStream(filePath + indexFile, std::ios::in);

    if (!fileStream.eof()) {
        getline(fileStream, line);
    } else {
        std::cout << "Scene is missing!\n";
        return;
    }

    if (line == "#dynamo") {
        while (!fileStream.eof()) {
            getline(fileStream, line);
            fileContents.push_back(line);
        }
        std::cout << "DYNAMO!\n";
    }
}

