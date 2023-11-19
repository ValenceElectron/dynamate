#include "Draw.hpp"

Draw::Draw(GLFWwindow* window, int width, int height) {
    currentShader = OGLSetup::createShaderProgram("render/shaders/vertShader.glsl", "render/shaders/fragShader.glsl");
    objectLocX = 0.0f; objectLocY = 0.0f; objectLocZ = 5.0f;

    this->width = width; this->height = height;

    OGLSetup::createProjectionMatrix(window, width, height, aspect, pMat);
    SetupVertices();
}

void Draw::SetupVertices() {
    Tetrahedron tetra;
    float objectVerts[36] = { 0 };
    tetra.getVertexCoordinates(objectVerts);

    /*for (int i = 0; i < tetra.numberOfVertexCoordinates(); i++) {
        std::cout << objectVerts[i] << std::endl;
    }

    std::cout << tetra.numberOfVertexCoordinates() << std::endl;*/

    glGenVertexArrays(numVAOs, vao);
    glBindVertexArray(vao[0]);
    glGenBuffers(numVBOs, vbo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(objectVerts), objectVerts, GL_STATIC_DRAW);
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
    glUseProgram(currentShader);

    tMat = glm::translate(glm::mat4(1.0f), glm::vec3(objectLocX, objectLocY, objectLocZ));
    rMat = glm::rotate(glm::mat4(1.0f), 0.7f * (float) currentTime, glm::vec3(0.0f, 1.0f, 0.0f));
    mMat = tMat * rMat;

    mLoc = glGetUniformLocation(currentShader, "mMat");
    vLoc = glGetUniformLocation(currentShader, "vMat");
    pLoc = glGetUniformLocation(currentShader, "pMat");
    glUniformMatrix4fv(mLoc, 1, GL_FALSE, glm::value_ptr(mMat));
    glUniformMatrix4fv(vLoc, 1, GL_FALSE, glm::value_ptr(vMat));
    glUniformMatrix4fv(pLoc, 1, GL_FALSE, glm::value_ptr(pMat));

    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glDrawArrays(GL_TRIANGLES, 0, 12);
}
