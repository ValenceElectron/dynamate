// Camera class for the homework A2 requirement
#include "Camera.hpp"
#include <iostream>

using namespace std;

Camera::Camera(float x, float y, float z) {
    u = glm::vec4(1.0f, 0.0f, 0.0f, 0.0f);
    v = glm::vec4(0.0f, 1.0f, 0.0f, 0.0f);
    n = glm::vec4(0.0f, 0.0f, 1.0f, 0.0f);
    c = glm::vec4(x, y, z, 1.0f);
};

glm::vec3 Camera::GetC() {
    return c;
};

glm::vec4 Camera::GetU() {
    return u;
}

glm::vec4 Camera::GetV() {
    return v;
}

glm::vec4 Camera::GetN() {
    return n;
}

void Camera::MoveLeft() {
    c = c - (0.5f * u);
};

void Camera::MoveRight() {
    c = c + (0.5f * u);
};

void Camera::MoveForward() {
    c = c - (0.5f * n);
};

void Camera::MoveBackward() {
    c = c + (0.5f * n);
};

void Camera::MoveUp() {
    c = c + (0.5f * v);
};

void Camera::MoveDown() {
    c = c - (0.5f * v);
}

void Camera::RotateUp() {
    v = glm::rotate(v, glm::radians(5.0f), glm::vec3(u));
    n = glm::rotate(n, glm::radians(5.0f), glm::vec3(u));
}

void Camera::RotateDown() {
    v = glm::rotate(v, glm::radians(-5.0f), glm::vec3(u));
    n = glm::rotate(n, glm::radians(-5.0f), glm::vec3(u));
}

void Camera::RotateRight() {
    u = glm::rotate(u, glm::radians(-5.0f), glm::vec3(v));
    n = glm::rotate(n, glm::radians(-5.0f), glm::vec3(v));
}

void Camera::RotateLeft() {
    u = glm::rotate(u, glm::radians(5.0f), glm::vec3(v));
    n = glm::rotate(n, glm::radians(5.0f), glm::vec3(v));
}