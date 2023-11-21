#include "DrawableObject.hpp"

DrawableObject::DrawableObject() { }

DrawableObject::DrawableObject(float *pos, float *vertices, int numberOfVertices) {
    for (int i = 0; i < 3; i++) {
        position[i] = pos[i];
    }

    vertexCoordinates = new float[numberOfVertices];
    numVertexCoordinates = numberOfVertices;

    for (int i = 0; i < numberOfVertices; i++) {
        vertexCoordinates[i] = vertices[i];
    }
}

void DrawableObject::setVertices(float *array) {
    vertexCoordinates = new float[numVertexCoordinates];
    for (int i = 0; i < getNumberOfVertices(); i++) { 
        vertexCoordinates[i] = array[i];
    }
}

void DrawableObject::setNumberOfVertices(int num) { numVertexCoordinates = num; }

void DrawableObject::setPosition(float *pos) {
   for (int i = 0; i < 3; i++) {
        position[i] = pos[i];
   }
}

void DrawableObject::setShader(GLuint shader) { 
    this->shader = shader;
}

void DrawableObject::getVertices(float *array) {
   for (int i = 0; i < numVertexCoordinates; i++) { array[i] = vertexCoordinates[i]; } 
}

int DrawableObject::getNumberOfVertices() { return numVertexCoordinates; }

glm::vec3 DrawableObject::getPositionV3() { return glm::vec3(position[0], position[1], position[2]); }

void DrawableObject::getPosition(float *pos) {
   for (int i = 0; i < 3; i++) {
        pos[i] = position[i];
   }
}


GLuint DrawableObject::getShader() { return shader; }

void DrawableObject::draw(double currentTime, glm::mat4 vMat, glm::mat4 pMat, GLuint vbo, int numberOfVertices) {
    GLuint shader = getShader();
    glUseProgram(shader);

    tMat = glm::translate(glm::mat4(1.0f), getPositionV3()); // Translation matrix
    mMat = tMat;
    /*rMat = glm::rotate(glm::mat4(1.0f), 0.7f * (float) currentTime, glm::vec3(0.0f, 1.0f, 0.0f)); // Rotation Matrix
    mMat = tMat * rMat; // Translation matrix * Rotation matrix = model matrix*/

    mLoc = glGetUniformLocation(shader, "mMat");
    vLoc = glGetUniformLocation(shader, "vMat");
    pLoc = glGetUniformLocation(shader, "pMat");
    glUniformMatrix4fv(mLoc, 1, GL_FALSE, glm::value_ptr(mMat));
    glUniformMatrix4fv(vLoc, 1, GL_FALSE, glm::value_ptr(vMat));
    glUniformMatrix4fv(pLoc, 1, GL_FALSE, glm::value_ptr(pMat));

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glDrawArrays(GL_TRIANGLES, 0, numberOfVertices/3);
}
