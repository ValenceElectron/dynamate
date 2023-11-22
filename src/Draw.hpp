#ifndef DRAW_H
#define DRAW_H

#include "utils/DrawableObjectManager.hpp"
#include "utils/ObjectLoader.hpp"
#include "utils/objects/DrawableObject.hpp"
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

    //DrawableObjectManager objManager;
    ObjectLoader* objLoader;

    void drawObjects(double currentTime, DrawableObjectManager& objManager);

public:
    Draw(DrawableObjectManager& objManager);
    void startDrawing(double currentTime, DrawableObjectManager& objManager);
};

#endif
