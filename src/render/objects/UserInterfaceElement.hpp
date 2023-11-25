#ifndef USERINTERFACEELEMENT_H
#define USERINTERFACEELEMENT_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <iostream>
#include "DrawableObject.hpp"

class UserInterfaceElement : public DrawableObject {
public:
    UserInterfaceElement(std::string objType, float *pos, float scale, float *vertices, int numberOfVertices, double *buttonBounds);

    void getButtonBounds(double *array);
    bool isVisible();
    void setVisibility(bool vis);
    void setButtonBounds(double *array);
    
    virtual void isClicked(double x, double y);
    void draw(double currentTime, glm::mat4 vMat, glm::mat4 pMat);
    
protected:
    double buttonBounds[4];
    bool visible = false;
};

class MainMenuButton : public UserInterfaceElement {
public:
    MainMenuButton(std::string objType, float *pos, float scale, float *vertices, int numberOfVertices, double *buttonBounds);
    void isClicked(double x, double y);
private:
};

#endif
