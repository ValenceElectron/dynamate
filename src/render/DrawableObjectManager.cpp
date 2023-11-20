#include "DrawableObjectManager.hpp"

DrawableObjectManager::DrawableObjectManager() { 
    numVBOs = 0; numUsedVBOs = 0;

    glGenVertexArrays(numVAOs, vao);
    glBindVertexArray(vao[0]);
}

void DrawableObjectManager::addObject(DrawableObject *obj) {
    std::cout << "Pushing object into list...\n";

    struct drawableChunk chunk;
    chunk.obj = obj;

    //objectBuffer.push_back(obj);
    numVBOs++;
    vbo.resize(numVBOs);
    std::cout << "Buffers resized.\n";
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
}

DrawableObjectManager::drawableChunk DrawableObjectManager::getNext() {
    //std::cout << "getting next drawableChunk...\n";
    return objectList.front();
}

DrawableObject* DrawableObjectManager::getMostRecent() {
    return objectList.back().obj;
}
