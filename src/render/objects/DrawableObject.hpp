#ifndef DRAWABLEOBJECT_H
#define DRAWABLEOBJECT_H

#include <GL/glew.h>
#include <cmath>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

class DrawableObject {
private:
    float *vertexCoordinates;
    int numVertexCoordinates;
    float position[3];
    GLuint shader;
    std::string objectType = "";

public:
    glm::mat4 mMat, tMat, rMat;
    GLuint mLoc, vLoc, pLoc;

    DrawableObject();
    DrawableObject(std::string objType, float *pos, float *vertices, int numberOfVertices);
    virtual ~DrawableObject() = default;

    void setVertices(float *array);
    void setNumberOfVertices(int num);
    void setPosition(float *pos);
    void setShader(GLuint shader);

    void getVertices(float *array);
    int getNumberOfVertices();
    void getPosition(float *pos);
    glm::vec3 getPositionV3();
    GLuint getShader();
    std::string getObjectType();

    void draw(double currentTime, glm::mat4 vMat, glm::mat4 pMat, GLuint vbo, int numberOfVertices);
};

#endif
