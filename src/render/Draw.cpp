#include "Draw.hpp"

Draw::Draw() {
    objLoader = new ObjectLoader(objManager);
    pMat = glm::ortho(-5.0f, 5.0f, -5.0f, 5.0f, 0.0f, 100.0f); // Orthographic perspective to achieve 2D

    // setupVertexBuffers() must be called in Draw's constructor but after objLoader.
    // it handles the vertex buffers for all DrawableObjects in objManager at once.
    objManager.setupVertexBuffers();
}


void Draw::startDrawing(double currentTime) {
    glClear(GL_DEPTH_BUFFER_BIT);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    vMat = glm::inverse(glm::mat4(camera.GetU(), camera.GetV(), camera.GetN(), glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)))
            * glm::translate(glm::mat4(1.0f), glm::vec3(-camera.GetC().x, -camera.GetC().y, -camera.GetC().z));

    DrawObject(currentTime);
}

void Draw::DrawObject(double currentTime) {
    int numberOfObjects = objManager.getNumberOfObjects();
    for (int i = 0; i < numberOfObjects; i++) {
        DrawableObjectManager::drawableChunk chunk = objManager.getNext();
        //std::cout << "Drawing vertex buffer: " << chunk.vertexBuffer << std::endl;
        chunk.obj->draw(currentTime, vMat, pMat, chunk.vertexBuffer, chunk.obj->getNumberOfVertices());
    }
}
