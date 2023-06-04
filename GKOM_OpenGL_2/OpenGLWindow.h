#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include "Program.h"
#include "Utilities.h"

class OpenGLWindow
{
public:

	OpenGLWindow();
	~OpenGLWindow();

	bool InitWindow();

	void InitScene();

	void MainLoop();

private:

	GLFWwindow* _window;

	Program transformationProgram;
	Program phongProgram;

	GLuint boxVAO;
	GLenum boxVAOPrimitive;
	GLuint cubeVAO;
	GLenum cubeVAOPrimitive;

	unsigned int boxVAOVertexCount;
	unsigned int cubeVAOVertexCount;

	void processInput();

	glm::vec2 windowResolution;
	float fieldOfView;

	glm::mat4 projectionMatrix;
	glm::mat4 cameraMatrix;
	glm::mat4 modelMatrix;

	glm::vec3 cameraPosition;
	glm::vec3 cameraDirection;
	glm::vec3 cameraUp;
	float cameraSpeed;

};
