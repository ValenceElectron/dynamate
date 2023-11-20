#ifndef DRAWABLEOBJECT_H
#define DRAWABLEOBJECT_H

#include <GL/glew.h>
#include <cmath>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

/*class IDrawable {
public:
    virtual void draw(double currentTime, GLuint vMat, GLuint pMat, int vboNum) = 0;
};*/

class DrawableObject {
private:
    float *vertexCoordinates;
    int numVertexCoordinates;
    float position[3];
    glm::vec3 positionVector;
    GLuint shader;

public:
    glm::mat4 mMat, tMat, rMat;
    GLuint mLoc, vLoc, pLoc;

    DrawableObject();
    DrawableObject(float *pos, float *vertices, int numberOfVertices);
    virtual ~DrawableObject() = default;

    void setVertices(float *array);
    void setNumberOfVertices(int num);
    void setPosition(float *pos);
    void setShader(GLuint shader);

    void getVertices(float *array);
    int getNumberOfVertices();
    void getPosition(float *pos);
    glm::vec3 getPosition();
    GLuint getShader();

    void draw(double currentTime, glm::mat4 vMat, glm::mat4 pMat, GLuint vbo);
};

class Tetrahedron : public DrawableObject {
public:
    Tetrahedron(float *pos);
    void draw(double currentTime, glm::mat4 vMat, glm::mat4 pMat, GLuint vbo);
};

#endif
