/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef LOADER_H
#define LOADER_H

#include <string>
#include <list>
#include <vector>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <sstream>
#include "OGLSetup.hpp"

class Loader {
public:
    Loader(float aspRatio);
    void scanDirectory();

protected:
    std::string filePath;
    std::string indexFile;
    std::list<std::string> fileContents;
    std::list<std::string>::iterator fileContentIterator;

    int numberOfObjectsInScene;
    float aspectRatio;
};

#endif
