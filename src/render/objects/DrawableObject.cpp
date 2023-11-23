#include "DrawableObject.hpp"

DrawableObject::DrawableObject() { }

DrawableObject::DrawableObject(std::string objType, float *pos, float scale, float *vertices, int numberOfVertices) {
    objectType = objType;

    for (int i = 0; i < 3; i++) {
        position[i] = pos[i];
    }

    objectScale = scale;

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

void DrawableObject::setScale(float scale) { objectScale = scale; }

void DrawableObject::setVBO(GLuint vertexBuffer) { vbo = vertexBuffer; }

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
std::string DrawableObject::getObjectType() { return objectType; }
float DrawableObject::getScale() { return objectScale; }

void DrawableObject::draw(double currentTime, glm::mat4 vMat, glm::mat4 pMat) {
    glUseProgram(shader);

    // Translations happen by getting the current object position
    tMat = glm::translate(glm::mat4(1.0f), getPositionV3()); // Translation matrix

    // Use function to define where the rotation happens
    //rMat = glm::rotate(glm::mat4(1.0f), getRotation(), glm::vec3(1.0f, 1.0f, 0.0f)); // Rotation Matrix

    // last element of the vec3 is left as 0.0f because we're in 2D. If 3D, scale that too, since it's the scale along the z-axis.
    sMat = glm::scale(glm::mat4(1.0f), glm::vec3(objectScale, objectScale, 0.0f)); // Scale matrix
    
    // Model matrix = Transform matrix * Rotation matrix * Scale matrix (order is specific)
    mMat = tMat * sMat;
    // If wanting to do 3D graphics, it'd be best to refactor from using matrices to quaternions.
    // Matrices are prone to gimbal lock, quaternions aren't.


    //rMat = glm::rotate(glm::mat4(1.0f), 0.7f * (float) currentTime, glm::vec3(0.0f, 1.0f, 0.0f)); // Rotation Matrix

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
    glDrawArrays(GL_TRIANGLES, 0, numVertexCoordinates/3);
}
