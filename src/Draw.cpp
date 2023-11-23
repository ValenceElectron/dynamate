#include "Draw.hpp"

Draw::Draw(DrawableObjectManager& objManager, int windowWidth, int windowHeight) {
    setupProjectionMatrix(windowWidth, windowHeight);
    objLoader = new ObjectLoader(objManager, aspectRatio);

    // setupVertexBuffers() must be called in Draw's constructor but after objLoader.
    // it handles the vertex buffers for all DrawableObjects in objManager at once.
    objManager.setupVertexBuffers();
}

void Draw::setupProjectionMatrix(int windowWidth, int windowHeight) {
    aspectRatio = (float) windowWidth / (float) windowHeight;
    //pMat = glm::ortho(0.0f, (float) windowWidth, 0.0f, (float) windowHeight, 0.0f, 100.0f);
    pMat = glm::ortho(0.0f, pMatBounds * aspectRatio, 0.0f, pMatBounds, 0.0f, 100.0f);
}

void Draw::startDrawing(double currentTime, DrawableObjectManager& objManager) {
    glClear(GL_DEPTH_BUFFER_BIT);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // vMat gets defined here in case we want any camera movement. vMat needs to get updated every frame
    // when we move the camera
    vMat = glm::inverse(glm::mat4(camera.GetU(), camera.GetV(), camera.GetN(), glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)))
            * glm::translate(glm::mat4(1.0f), glm::vec3(-camera.GetC().x, -camera.GetC().y, -camera.GetC().z));

    drawObjects(currentTime, objManager);
}

void Draw::drawObjects(double currentTime, DrawableObjectManager& objManager) {
    int numberOfObjects = objManager.getNumberOfObjects();
    for (int i = 0; i < numberOfObjects; i++) {
        DrawableObjectManager::drawableChunk chunk = objManager.getNext();
        //std::cout << "Drawing vertex buffer: " << chunk.vertexBuffer << std::endl;
        chunk.obj->draw(currentTime, vMat, pMat, chunk.vertexBuffer, chunk.obj->getNumberOfVertices());
    }

    int numberOfElements = objManager.getNumberOfElements();
    for (int i = 0; i < numberOfElements; i++) {
        DrawableObjectManager::uiChunk* chunk = objManager.getNextUI();
        chunk->element->draw(currentTime, vMat, pMat, chunk->vertexBuffer, chunk->element->getNumberOfVertices());
    }
}
