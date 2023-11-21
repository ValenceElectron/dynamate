#include "DrawableObjectManager.hpp"

DrawableObjectManager::DrawableObjectManager() { 
    glGenVertexArrays(numVAOs, vao);
    glBindVertexArray(vao[0]);
}

void DrawableObjectManager::addObject(DrawableObject *obj) {
    std::cout << "Pushing object into list...\n";
    struct drawableChunk chunk;
    chunk.obj = obj;
    setupVertices(chunk);
}

void DrawableObjectManager::setupVertices(drawableChunk chunk) {
    std::cout << "Generating new vertex buffers...\n";

    GLuint vbosToGenerate[1];
    glGenBuffers(1, vbosToGenerate);

    float verts[chunk.obj->getNumberOfVertices()] = { 0 };
    chunk.obj->getVertices(verts);
    glBindBuffer(GL_ARRAY_BUFFER, vbosToGenerate[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

    chunk.vertexBuffer = vbosToGenerate[0];
    objectList.push_back(chunk);
    std::cout << "Vertex buffers completely setup.\n";
    initIterator();
}

DrawableObjectManager::drawableChunk DrawableObjectManager::getNext() {
    drawableChunk chunk = *currentIndex;

    if (objectList.size() > 1) {
        if (currentIndex == objectList.end()) { currentIndex = objectList.begin(); }
        else { currentIndex++; }
    }

    return chunk;
}

DrawableObject* DrawableObjectManager::getMostRecent() {
    return objectList.back().obj;
}

// This function is needed to make sure we don't init currentIndex when the list is empty
void DrawableObjectManager::initIterator() {
    if (isIteratorInit) return;

    currentIndex = objectList.begin();
    isIteratorInit = true;
}
