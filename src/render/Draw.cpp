#include "Draw.hpp"

Draw::Draw(GLFWwindow* window, int width, int height) {
    currentShader = OGLSetup::createShaderProgram("render/shaders/vertShader.glsl", "render/shaders/fragShader.glsl");
    std::cout << "Shader creation complete.\n";

    this->width = width; this->height = height;

    OGLSetup::createProjectionMatrix(window, width, height, aspect, pMat);
    std::cout << "Projection matrix creation complete.\n";

    std::cout << "Adding tetrahedron to object manager buffer...\n";

    float pos[3] = {0.0f, 0.0f, 5.0f};
    objManager.addObject(new Tetrahedron(pos));
    //std::cout << "shader: " << currentShader << std::endl;
    objManager.getMostRecent()->setShader(currentShader);
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
    //std::cout << "Drawing tetrahedron...\n";
    DrawableObjectManager::drawableChunk chunk = objManager.getNext();
    Tetrahedron* tet = dynamic_cast<Tetrahedron*>(chunk.obj);

    int numV = tet->getNumberOfVertices();
    float array[numV] = { 0 };
    tet->getVertices(array);
    //std::cout << chunk.vertexBuffer << std::endl;
    //for (float i : array) { std::cout << i << "\n"; }
    tet->draw(currentTime, vMat, pMat, chunk.vertexBuffer);
}
