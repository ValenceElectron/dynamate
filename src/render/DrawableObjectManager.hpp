#ifndef DRAWABLEOBJECTMANAGER_H
#define DRAWABLEOBJECTMANAGER_H

#include <list>
#include "objects/DrawableObject.hpp"

#define numVAOs 1

class DrawableObjectManager {
private:
    std::list<DrawableObject*> objectBuffer;
    std::vector<GLuint> vbo;
    int numVBOs;
    int numUsedVBOs;
    GLuint vao[numVAOs];
    //GLuint vbo[numVBOs];

public:
    DrawableObjectManager();
    struct drawableChunk {
        DrawableObject* obj;
        GLuint vertexBuffer;
    };

    void addObject(DrawableObject *obj);
    void setupVertices();
    drawableChunk getNext();
    DrawableObject* getMostRecent();
};

#endif
