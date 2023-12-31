/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

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
protected:
    float *vertexCoordinates;
    int numVertexCoordinates;
    float position[3];
    float objectScale;
    GLuint shader, vbo;
    std::string objectType = "";

public:
    glm::mat4 mMat, tMat, rMat, sMat;
    GLuint mLoc, vLoc, pLoc;

    DrawableObject();
    DrawableObject(std::string objType, float *pos, float scale, float *vertices, int numberOfVertices);
    virtual ~DrawableObject() = default;

    void setVertices(float *array);
    void setNumberOfVertices(int num);
    void setPosition(float *pos);
    void setShader(GLuint shader);
    void setScale(float scale);
    void setVBO(GLuint vertexBuffer);

    void getVertices(float *array);
    int getNumberOfVertices();
    void getPosition(float *pos);
    glm::vec3 getPositionV3();
    GLuint getShader();
    std::string getObjectType();
    float getScale();

    void draw(double currentTime, glm::mat4 vMat, glm::mat4 pMat);
};

#endif
