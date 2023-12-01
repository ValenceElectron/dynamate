#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>

class Camera {
private:
    glm::vec4 u, v, n, c;

public:
    Camera(float x, float y, float z);
    glm::vec3 GetC();
    glm::vec4 GetU();
    glm::vec4 GetV();
    glm::vec4 GetN();

    void MoveLeft();
    void MoveRight();
    void MoveForward();
    void MoveBackward();
    void MoveUp();
    void MoveDown();

    void RotateLeft();
    void RotateRight();
    void RotateUp();
    void RotateDown();
};

#endif
