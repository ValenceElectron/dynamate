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

    objectBuffer.push_back(chunk);
    std::cout << "Vertex buffers completely setup.\n";
}

DrawableObjectManager::drawableChunk DrawableObjectManager::getNext() {
    drawableChunk chunk = objectBuffer.at(currentIndex);

    if ((currentIndex + 1) >= objectBuffer.size()) { currentIndex = 0; }
    else { currentIndex++; }

    return chunk;
}

DrawableObject* DrawableObjectManager::getMostRecent() {
    return objectBuffer.back().obj;
}
