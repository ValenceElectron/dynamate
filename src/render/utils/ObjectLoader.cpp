#include "ObjectLoader.hpp"

ObjectLoader::ObjectLoader() { }

void ObjectLoader::addObject(DrawableObjectManager& objManager) {
    GLuint shader = OGLSetup::createShaderProgram("render/shaders/vertShader.glsl", "render/shaders/fragShader.glsl");
    
    float pos[3] = {0.0f, 0.0f, 5.0f};
    objManager.addObject(new Tetrahedron(pos));
    objManager.getMostRecent()->setShader(shader);
}
