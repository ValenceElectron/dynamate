#include "UserInterfaceElement.hpp"

UserInterfaceElement::UserInterfaceElement(std::string objType, float *pos, float scale, float *vertices, int numberOfVertices, double *buttonBounds)
: DrawableObject(objType, pos, scale, vertices, numberOfVertices) {
    setButtonBounds(buttonBounds);
}

void UserInterfaceElement::getButtonBounds(double *array) {
    for (int i = 0; i < 4; i++) { array[i] = buttonBounds[i]; }
}

bool UserInterfaceElement::isVisible() { return visible; }

void UserInterfaceElement::setVisibility(bool vis) { visible = vis; }

void UserInterfaceElement::setButtonBounds(double *array) {
    for (int i = 0; i < 4; i++) { buttonBounds[i] = array[i]; }
}

void UserInterfaceElement::isClicked(double x, double y) { 
    std::cout << "Click!\n";
}

void UserInterfaceElement::draw(double currentTime, glm::mat4 vMat, glm::mat4 pMat) {
    if (isVisible()) {
        glUseProgram(shader);

        // Translations happen by getting the current object position
        tMat = glm::translate(glm::mat4(1.0f), getPositionV3()); // Translation matrix

        // Use function to define where the rotation happens
        //rMat = glm::rotate(glm::mat4(1.0f), getRotation(), glm::vec3(1.0f, 1.0f, 0.0f)); // Rotation Matrix

        // last element of the vec3 is left as 0.0f because we're in 2D. If 3D, scale that too, since it's the scale along the z-axis.
        sMat = glm::scale(glm::mat4(1.0f), glm::vec3(objectScale, objectScale, 0.0f)); // Scale matrix

        // Model matrix = Transform matrix * Rotation matrix * Scale matrix (order is specific)
        mMat = tMat * sMat;

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
        glDrawArrays(GL_TRIANGLES, 0, numVertexCoordinates/3); // numVertexCoordinates/3 = the total number of vertices
    } else { }
}
