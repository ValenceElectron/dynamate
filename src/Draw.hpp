/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef DRAW_H
#define DRAW_H

#include "render/DrawableObjectManager.hpp"
#include "render/UserInterfaceManager.hpp"
#include "utils/ObjectLoader.hpp"
#include "utils/UserInterfaceLoader.hpp"
#include "utils/Camera.hpp"
#include "utils/OGLSetup.hpp"

#define numVAOs 1
#define numVBOs 1

class Draw {
private:
    GLuint currentShader;

    Camera camera{0.0f, 0.0f, 10.0f};
    float cameraX, cameraY, cameraZ;
    int numberOfObjects = 0;
    int numberOfElements = 0;

    glm::mat4 pMat, vMat;
    float aspectRatio;
    float pMatBounds = 5.0f;

    ObjectLoader* objLoader;
    UserInterfaceLoader* uiLoader;

    void setupProjectionMatrix(int windowWidth, int windowHeight);
    void drawObjects(double currentTime, DrawableObjectManager& objManager, UserInterfaceManager& uiManager);

public:
    Draw(DrawableObjectManager& objManager, UserInterfaceManager& uiManager, int windowWidth, int windowHeight);
    void startDrawing(double currentTime, DrawableObjectManager& objManager, UserInterfaceManager& uiManager);
};

#endif
