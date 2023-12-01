/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

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

