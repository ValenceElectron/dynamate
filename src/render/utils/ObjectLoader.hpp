#ifndef OBJECTLOADER_H
#define OBJECTLOADER_H

#include <string>
#include <list>
#include <iostream>
#include <fstream>
#include "DrawableObjectManager.hpp"
#include "OGLSetup.hpp"

class ObjectLoader {
public:
    ObjectLoader();
    void addObject(DrawableObjectManager& objManager);

private:
    //void loadObject(std::string filepath);
};

#endif
