#include "DrawableObjectManager.hpp"

DrawableObjectManager::DrawableObjectManager() { 
    currentDrawableIndex = 0;
    currentUIIndex = 0;
}

void DrawableObjectManager::addObject(DrawableObject *obj) {
    std::cout << "Pushing object into vector...\n";
    struct drawableChunk chunk;
    chunk.obj = obj;
    objectBuffer.push_back(chunk);
}

DrawableObjectManager::drawableChunk DrawableObjectManager::getNext() {
    drawableChunk chunk = objectBuffer.at(currentDrawableIndex);

    if ((currentDrawableIndex + 1) >= objectBuffer.size()) { currentDrawableIndex = 0; }
    else { currentDrawableIndex++; }

    return chunk;
}

int DrawableObjectManager::getNumberOfObjects() {
    return (int) objectBuffer.size();
}

void DrawableObjectManager::addElement(UserInterfaceElement *element) {
    struct uiChunk chunk;
    chunk.element = element;
    uiBuffer.push_back(chunk);
}

DrawableObjectManager::uiChunk* DrawableObjectManager::getNextUI() {
    if (!uiBuffer.at(currentUIIndex).element->isVisible()) { uiBuffer.at(currentUIIndex).element->setVisibility(true); }
    uiChunk* chunk = &uiBuffer.at(currentUIIndex);

    if ((currentUIIndex + 1) >= uiBuffer.size()) { currentUIIndex = 0; }
    else { currentUIIndex++; }

    return chunk;
}

int DrawableObjectManager::getNumberOfElements() {
    return uiBuffer.size();
}

void DrawableObjectManager::handleMouseClick() {
    
}

void DrawableObjectManager::setupVertexBuffers() {
    glGenVertexArrays(numVAOs, vao);
    glBindVertexArray(vao[0]);

    std::cout << "Generating vertex buffers...\n";
    int numberOfObjects = objectBuffer.size() + uiBuffer.size();
    std::cout << "Number of buffers to generate: " << numberOfObjects << std::endl;
    GLuint vbosToGenerate[numberOfObjects];
    glGenBuffers(numberOfObjects, vbosToGenerate);

    for (int i = 0; i < numberOfObjects; i++) {
        if (i < objectBuffer.size()) {
            DrawableObjectManager::drawableChunk *chunk = &objectBuffer.at(i);
            float verts[chunk->obj->getNumberOfVertices()] = { 0 };
            chunk->obj->getVertices(verts);
            glBindBuffer(GL_ARRAY_BUFFER, vbosToGenerate[i]);
            glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

            std::cout << "Vertex buffer: " << vbosToGenerate[i] << std::endl;
            chunk->vertexBuffer = vbosToGenerate[i];
        } else {
            int j = i - objectBuffer.size();
            DrawableObjectManager::uiChunk *chunk = &uiBuffer.at(j);
            float verts[chunk->element->getNumberOfVertices()] = { 0 };
            chunk->element->getVertices(verts);
            glBindBuffer(GL_ARRAY_BUFFER, vbosToGenerate[i]);
            glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

            std::cout << "Vertex buffer: " << vbosToGenerate[i] << std::endl;
            chunk->vertexBuffer = vbosToGenerate[i];
        }
    }
}

