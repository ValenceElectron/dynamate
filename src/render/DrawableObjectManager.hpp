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
