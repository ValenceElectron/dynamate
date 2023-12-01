/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

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

