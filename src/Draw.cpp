/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "Draw.hpp"

Draw::Draw(DrawableObjectManager& objManager, UserInterfaceManager& uiManager, int windowWidth, int windowHeight) {
    setupProjectionMatrix(windowWidth, windowHeight);
    objLoader = new ObjectLoader(objManager, aspectRatio);
    uiLoader = new UserInterfaceLoader(uiManager, aspectRatio, windowWidth, windowHeight);

    // setupVertexBuffers() must be called in Draw's constructor but after objLoader.
    // it handles the vertex buffers for all DrawableObjects in objManager
    // and all UserInterfaceElements in uiManager, at once.
    OGLSetup::setupVertexBuffers(objManager, uiManager);
}

void Draw::setupProjectionMatrix(int windowWidth, int windowHeight) {
    aspectRatio = (float) windowWidth / (float) windowHeight;
    //pMat = glm::ortho(0.0f, (float) windowWidth, 0.0f, (float) windowHeight, 0.0f, 100.0f);
    pMat = glm::ortho(0.0f, pMatBounds * aspectRatio, 0.0f, pMatBounds, 0.0f, 100.0f);
}

void Draw::startDrawing(double currentTime, DrawableObjectManager& objManager, UserInterfaceManager& uiManager) {
    glClear(GL_DEPTH_BUFFER_BIT);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // vMat gets defined here in case we want any camera movement. vMat needs to get updated every frame
    // when we move the camera
    vMat = glm::inverse(glm::mat4(camera.GetU(), camera.GetV(), camera.GetN(), glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)))
            * glm::translate(glm::mat4(1.0f), glm::vec3(-camera.GetC().x, -camera.GetC().y, -camera.GetC().z));

    drawObjects(currentTime, objManager, uiManager);
}

void Draw::drawObjects(double currentTime, DrawableObjectManager& objManager, UserInterfaceManager& uiManager) {
    numberOfObjects = objManager.getBufferSize();
    for (int i = 0; i < numberOfObjects; i++) {
        objManager.getNext()->draw(currentTime, vMat, pMat);
    }

    numberOfElements = uiManager.getBufferSize();
    for (int i = 0; i < numberOfElements; i++) {
        uiManager.getNext()->draw(currentTime, vMat, pMat);
    }
}
