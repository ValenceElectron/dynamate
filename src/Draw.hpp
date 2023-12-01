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
