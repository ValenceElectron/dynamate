#ifndef DRAWABLEOBJECTMANAGER_H
#define DRAWABLEOBJECTMANAGER_H

#include "objects/DrawableObject.hpp"
#include "objects/UserInterfaceElement.hpp"

#define numVAOs 1

class DrawableObjectManager {
public:
    struct drawableChunk {
        DrawableObject* obj;
        GLuint vertexBuffer;
    };

    struct uiChunk {
        UserInterfaceElement* element;
        GLuint vertexBuffer;
    };

    DrawableObjectManager();

    void addObject(DrawableObject *obj);
    drawableChunk getNext();
    int getNumberOfObjects();

    void addElement(UserInterfaceElement *element);
    uiChunk* getNextUI();
    int getNumberOfElements();
    void handleMouseClick();

    void setupVertexBuffers();

private:
    std::vector<drawableChunk> objectBuffer;
    std::vector<uiChunk> uiBuffer;
    int currentDrawableIndex;
    int currentUIIndex;
    GLuint vao[numVAOs];
};

#endif
