#include "DrawableObjectManager.hpp"
#include "objects/DrawableObject.hpp"
#include "utils/Camera.hpp"
#include "utils/OGLSetup.hpp"

#define numVAOs 1
#define numVBOs 1

class Draw {
private:
    GLuint currentShader;
    GLuint vao[numVAOs];
    GLuint vbo[numVBOs];

    Camera camera{0.0f, 0.0f, 10.0f};
    float cameraX, cameraY, cameraZ;
    float objectLocX, objectLocY, objectLocZ;
    int windowWidth, windowHeight, monitorX, monitorY;
    int width, height;

    GLuint mLoc, vLoc, pLoc;
    float aspect;
    glm::mat4 pMat, vMat, mMat, tMat, rMat;

    DrawableObjectManager objManager;

    void SetupVertices();
    void DrawObject(double currentTime);

public:
    Draw(GLFWwindow* window, int width, int height);
    void startDrawing(double currentTime);
};
    //init(window);
