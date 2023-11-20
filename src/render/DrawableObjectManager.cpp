#include "DrawableObjectManager.hpp"

DrawableObjectManager::DrawableObjectManager() { 
    numVBOs = 0; numUsedVBOs = 0;

    glGenVertexArrays(numVAOs, vao);
    glBindVertexArray(vao[0]);
}

void DrawableObjectManager::addObject(DrawableObject *obj) {
    std::cout << "Pushing object into list...\n";
    objectBuffer.push_back(obj);
    numVBOs++;
    vbo.resize(numVBOs);
    std::cout << "Buffers resized.\n";
}

void DrawableObjectManager::setupVertices() {
    std::cout << "Generating new vertex buffers...\n";
    for (int i = numUsedVBOs; i < numVBOs; i++) {
        GLuint *newVBO;
        glGenBuffers(1, newVBO);
        vbo.push_back(newVBO[0]);
    }
    
    /*auto it = vbo.begin();
    it += numUsedVBOs;*/
    std::cout << "Assigning new vertex buffers to objects...\n";
    for (DrawableObject *obj : objectBuffer) {
        float verts[obj->getNumberOfVertices()] = { 0 };
        obj->getVertices(verts);

        glBindBuffer(GL_ARRAY_BUFFER, vbo.at(numUsedVBOs));
        glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
        numUsedVBOs++;
    }

    std::cout << "Vertex buffers completely setup.\n";
}

DrawableObjectManager::drawableChunk DrawableObjectManager::getNext() {
    struct drawableChunk chunk;
    chunk.obj = objectBuffer.front();
    chunk.vertexBuffer = vbo.front();
    return chunk;
    //objectBuffer.pop_front();
}

DrawableObject* DrawableObjectManager::getMostRecent() {
    return objectBuffer.back();
}
