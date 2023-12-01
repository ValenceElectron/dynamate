#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>
#include <fstream>
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include "OGLSetup.hpp"
using namespace std;

OGLSetup::OGLSetup() {}

void OGLSetup::setupVertexBuffers(DrawableObjectManager& objManager, UserInterfaceManager& uiManager) {
    glGenVertexArrays(1, vao);
    glBindVertexArray(vao[0]);

    std::cout << "Generating vertex buffers...\n";
    int objBufferSize = objManager.getBufferSize();
    int uiBufferSize = uiManager.getBufferSize();

    int numberOfObjects = objBufferSize + uiBufferSize;
    std::cout << "Number of buffers to generate: " << numberOfObjects << std::endl;
    GLuint vbosToGenerate[numberOfObjects];
    glGenBuffers(numberOfObjects, vbosToGenerate);

    for (int i = 0; i < numberOfObjects; i++) {
        if (i < objBufferSize) {
            DrawableObject* pObj = objManager.getNext();
            float verts[pObj->getNumberOfVertices()] = { 0 };
            pObj->getVertices(verts);
            glBindBuffer(GL_ARRAY_BUFFER, vbosToGenerate[i]);
            glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

            std::cout << "Vertex buffer: " << vbosToGenerate[i] << std::endl;
            pObj->setVBO(vbosToGenerate[i]);
        } else {
            UserInterfaceElement* pElm = uiManager.getNext();
            float verts[pElm->getNumberOfVertices()] = { 0 };
            pElm->getVertices(verts);
            glBindBuffer(GL_ARRAY_BUFFER, vbosToGenerate[i]);
            glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

            std::cout << "Vertex buffer: " << vbosToGenerate[i] << std::endl;
            pElm->setVBO(vbosToGenerate[i]);
        }
    }
}

string OGLSetup::readShaderFile(string filePath) {
	string content;
	ifstream fileStream(filePath, ios::in);
	string line = "";
	while (!fileStream.eof()) {
		getline(fileStream, line);
		content.append(line + "\n");
	}
	fileStream.close();
	return content;
}

bool OGLSetup::checkOpenGLError() {
	bool foundError = false;
	int glErr = glGetError();
	while (glErr != GL_NO_ERROR) {
		cout << "glError: " << glErr << endl;
		foundError = true;
		glErr = glGetError();
	}
	return foundError;
}

void OGLSetup::printShaderLog(GLuint shader) {
	int len = 0;
	int chWrittn = 0;
	char *log;
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);
	if (len > 0) {
		log = (char *)malloc(len);
		glGetShaderInfoLog(shader, len, &chWrittn, log);
		cout << "Shader Info Log: " << log << endl;
		free(log);
	}
}

GLuint OGLSetup::prepareShader(int shaderTYPE, string shaderPath)
{	GLint shaderCompiled;
	string shaderStr = readShaderFile(shaderPath);
	const char *shaderSrc = shaderStr.c_str();
	GLuint shaderRef = glCreateShader(shaderTYPE);
	glShaderSource(shaderRef, 1, &shaderSrc, NULL);
	glCompileShader(shaderRef);
	checkOpenGLError();
	glGetShaderiv(shaderRef, GL_COMPILE_STATUS, &shaderCompiled);
	if (shaderCompiled != 1)
	{	if (shaderTYPE == 35633) cout << "Vertex ";
		if (shaderTYPE == 36488) cout << "Tess Control ";
		if (shaderTYPE == 36487) cout << "Tess Eval ";
		if (shaderTYPE == 36313) cout << "Geometry ";
		if (shaderTYPE == 35632) cout << "Fragment ";
		cout << "shader compilation error." << endl;
		printShaderLog(shaderRef);
	}
	return shaderRef;
}

void OGLSetup::printProgramLog(int prog) {
	int len = 0;
	int chWrittn = 0;
	char *log;
	glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &len);
	if (len > 0) {
		log = (char *)malloc(len);
		glGetProgramInfoLog(prog, len, &chWrittn, log);
		cout << "Program Info Log: " << log << endl;
		free(log);
	}
}

int OGLSetup::finalizeShaderProgram(GLuint sprogram)
{	GLint linked;
	glLinkProgram(sprogram);
	checkOpenGLError();
	glGetProgramiv(sprogram, GL_LINK_STATUS, &linked);
	if (linked != 1)
	{	cout << "linking failed" << endl;
		printProgramLog(sprogram);
	}
	return sprogram;
}

GLuint OGLSetup::createShaderProgram(string vp, string fp) {
	GLuint vShader = prepareShader(GL_VERTEX_SHADER, vp);
	GLuint fShader = prepareShader(GL_FRAGMENT_SHADER, fp);
	GLuint vfprogram = glCreateProgram();
	glAttachShader(vfprogram, vShader);
	glAttachShader(vfprogram, fShader);
	finalizeShaderProgram(vfprogram);
	return vfprogram;
}

