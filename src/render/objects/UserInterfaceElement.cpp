#include "UserInterfaceElement.hpp"

UserInterfaceElement::UserInterfaceElement(std::string objType, float *pos, float *vertices, int numberOfVertices, double *buttonBounds)
: DrawableObject(objType, pos, vertices, numberOfVertices) {
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

void UserInterfaceElement::draw(double currentTime, glm::mat4 vMat, glm::mat4 pMat, GLuint vbo, int numberOfVertices) {
    if (isVisible()) {
        GLuint shader = getShader();
        glUseProgram(shader);

        tMat = glm::translate(glm::mat4(1.0f), getPositionV3());
        mMat = tMat;

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
    } else { }
}
