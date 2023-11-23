#ifndef DRAW_H
#define DRAW_H

#include "render/DrawableObjectManager.hpp"
#include "utils/ObjectLoader.hpp"
#include "render/objects/DrawableObject.hpp"
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

    ObjectLoader* objLoader;

    void setupProjectionMatrix(int windowWidth, int windowHeight);
    void drawObjects(double currentTime, DrawableObjectManager& objManager);

public:
    Draw(DrawableObjectManager& objManager, int windowWidth, int windowHeight);
    void startDrawing(double currentTime, DrawableObjectManager& objManager);
};

#endif
