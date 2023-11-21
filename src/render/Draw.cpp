#include "Draw.hpp"

Draw::Draw() {
    objLoader = new ObjectLoader(objManager);
    pMat = glm::ortho(-5.0f, 5.0f, -5.0f, 5.0f, 0.0f, 100.0f); // Orthographic perspective to achieve 2D
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
    DrawableObjectManager::drawableChunk chunk = objManager.getNext();
    chunk.obj->draw(currentTime, vMat, pMat, chunk.vertexBuffer, chunk.obj->getNumberOfVertices());
}
