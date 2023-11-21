#include "DrawableObjectManager.hpp"

DrawableObjectManager::DrawableObjectManager() { 
    glGenVertexArrays(numVAOs, vao);
    glBindVertexArray(vao[0]);
    currentIndex = 0;
}

void DrawableObjectManager::addObject(DrawableObject *obj) {
    std::cout << "Pushing object into vector...\n";
    struct drawableChunk chunk;
    chunk.obj = obj;
    objectBuffer.push_back(chunk);
}

DrawableObjectManager::drawableChunk DrawableObjectManager::getNext() {
    drawableChunk chunk = objectBuffer.at(currentIndex);

    if ((currentIndex + 1) >= objectBuffer.size()) { currentIndex = 0; }
    else { currentIndex++; }

    return chunk;
}

int DrawableObjectManager::getNumberOfObjects() {
    return (int) objectBuffer.size();
}

DrawableObject* DrawableObjectManager::getMostRecent() {
    return objectBuffer.back().obj;
}

void DrawableObjectManager::setupVertexBuffers() {
    std::cout << "Generating vertex buffers...\n";
    int numberOfObjects = objectBuffer.size();
    GLuint vbosToGenerate[numberOfObjects];
    glGenBuffers(numberOfObjects, vbosToGenerate);

    for (int i = 0; i < numberOfObjects; i++) {
        DrawableObjectManager::drawableChunk *chunk = &objectBuffer.at(i);
        float verts[chunk->obj->getNumberOfVertices()] = { 0 };
        chunk->obj->getVertices(verts);
        glBindBuffer(GL_ARRAY_BUFFER, vbosToGenerate[i]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

        std::cout << "Vertex buffer: " << vbosToGenerate[i] << std::endl;
        chunk->vertexBuffer = vbosToGenerate[i];
    }
}

