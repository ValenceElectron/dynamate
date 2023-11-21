#ifndef OGLSETUP_H
#define OGLSETUP_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

class OGLSetup {
private:
	static std::string readShaderFile(std::string filePath);
	static void printShaderLog(GLuint shader);
	static void printProgramLog(int prog);
	static GLuint prepareShader(int shaderTYPE, std::string shaderPath);
	static int finalizeShaderProgram(GLuint sprogram);

public:
	OGLSetup();
	static bool checkOpenGLError();
	static GLuint createShaderProgram(std::string vp, std::string fp);
	static GLuint createShaderProgram(std::string vp, std::string gp, std::string fp);
	static GLuint createShaderProgram(std::string vp, std::string tCS, std::string tES, std::string fp);
	static GLuint createShaderProgram(std::string vp, std::string tCS, std::string tES, std::string gp, std::string fp);
};

#endif
