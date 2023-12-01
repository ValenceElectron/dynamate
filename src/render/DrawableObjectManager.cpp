#include "DrawableObjectManager.hpp"

DrawableObjectManager::DrawableObjectManager()
: ResourceManager() { }

void DrawableObjectManager::addToBuffer(DrawableObject *obj) {
    std::cout << "Pushing object into vector...\n";
    resourceBuffer.push_back(obj);
}

DrawableObject* DrawableObjectManager::getNext() {
    DrawableObject* object = resourceBuffer.at(currentIndex);

    if ((currentIndex + 1) >= resourceBuffer.size()) { currentIndex = 0; }
    else { currentIndex++; }

    return object;
}

int DrawableObjectManager::getBufferSize() { return resourceBuffer.size(); }

