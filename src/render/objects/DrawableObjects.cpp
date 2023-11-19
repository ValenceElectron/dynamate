#include "DrawableObjects.hpp"

void Tetrahedron::getVertexCoordinates(float *array) {
    float tetrahedron[36] = {
        -0.5f, -0.5f, -0.5f,    0.0f, -0.5f, 0.5f,      0.0f, 0.5f, 0.0f,                                   // Forward-left tri
        0.0f, -0.5f, 0.5f,      0.5f, -0.5f, -0.5f,     0.0f, 0.5f, 0.0f,                                   // Forward-right tri
        0.5f, -0.5f, -0.5f,     -0.5f, -0.5f, -0.5f,    0.0f, 0.5f, 0.0f,                                   // Backward tri
        0.0f, -0.5f, 0.5f,      -0.5f, -0.5f, -0.5f,    0.5f, -0.5f, -0.5f
    };
    
    for (int i = 0; i < 36; i++) { array[i] = tetrahedron[i]; }
}

int Tetrahedron::numberOfVertexCoordinates() { 
    return 36;
}
