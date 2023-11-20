#ifndef DRAWABLEOBJECTMANAGER_H
#define DRAWABLEOBJECTMANAGER_H

#include <list>
#include "objects/DrawableObject.hpp"

#define numVAOs 1

class DrawableObjectManager {
public:
    DrawableObjectManager();
    struct drawableChunk {
        DrawableObject* obj;
        GLuint vertexBuffer;
    };

    void addObject(DrawableObject *obj);
    void setupVertices(drawableChunk chunk);
    drawableChunk getNext();
    DrawableObject* getMostRecent();

private:
    std::list<DrawableObject*> objectBuffer;
    std::list<drawableChunk> objectList;
    std::vector<GLuint> vbo;
    int numVBOs;
    int numUsedVBOs;
    GLuint vao[numVAOs];
};

#endif
