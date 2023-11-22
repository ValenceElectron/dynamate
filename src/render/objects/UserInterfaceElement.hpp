#ifndef USERINTERFACEELEMENT_H
#define USERINTERFACEELEMENT_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <iostream>
#include "DrawableObject.hpp"

class UserInterfaceElement : public DrawableObject {
public:
    UserInterfaceElement(float *pos, float *vertices, int numberOfVertices, double *buttonBounds);

    void getButtonBounds(double *array);
    bool isVisible();
    void toggleVisibility();
    void setButtonBounds(double *array);
    
    virtual void isClicked(double x, double y) = 0;
    void draw(double currentTime, glm::mat4 vMat, glm::mat4 pMat, GLuint vbo, int numberOfVertices);
    
private:
    double buttonBounds[4];
    bool visible = false;
};

#endif
