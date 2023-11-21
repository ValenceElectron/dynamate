#ifndef DRAWABLEOBJECTMANAGER_H
#define DRAWABLEOBJECTMANAGER_H

#include "../objects/DrawableObject.hpp"

#define numVAOs 1

class DrawableObjectManager {
public:
    struct drawableChunk {
        DrawableObject* obj;
        GLuint vertexBuffer;
    };
    DrawableObjectManager();

    void addObject(DrawableObject *obj);
    drawableChunk getNext();
    int getNumberOfObjects();
    DrawableObject* getMostRecent();

    void setupVertices(drawableChunk chunk);
    void setupVertexBuffers();

private:
    std::vector<drawableChunk> objectBuffer;
    int currentIndex;
    bool isIteratorInit = false;
    GLuint vao[numVAOs];

    void getObjectAtIndex(int index);
};

#endif
