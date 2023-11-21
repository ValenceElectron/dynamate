#ifndef DRAWABLEOBJECTMANAGER_H
#define DRAWABLEOBJECTMANAGER_H

#include <list>
#include "../objects/DrawableObject.hpp"

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
    std::list<drawableChunk> objectList;
    std::list<drawableChunk>::iterator currentIndex;
    bool isIteratorInit = false;
    GLuint vao[numVAOs];

    void initIterator();
};

#endif
