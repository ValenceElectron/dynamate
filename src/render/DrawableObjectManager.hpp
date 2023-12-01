/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef DRAWABLEOBJECTMANAGER_H
#define DRAWABLEOBJECTMANAGER_H

#include "ResourceManager.hpp"
#include "objects/DrawableObject.hpp"

class DrawableObjectManager : public ResourceManager {
public:
    DrawableObjectManager();

    void addToBuffer(DrawableObject *obj);
    DrawableObject* getNext();
    int getBufferSize();

    void setupVertexBuffers();

private:
    std::vector<DrawableObject*> resourceBuffer;
    int currentIndex;
    GLuint vao[1];
};

#endif
